// Copyright 2023 Dasky (@daskygit), 2024 Choi Byungyoon (@byungyoonc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "graphics/display.h"
#include "graphics/quinquefive.qff.h"
#include "graphics/boot_anim.qgf.h"
#include "he_switch_matrix.h"
#include <stdio.h>

static painter_device_t      display;
static painter_font_handle_t font;
static deferred_token         anim_token;
static deferred_token         refresh_token;
static bool                   boot_done      = false;
static bool                   dashboard_init = false; // first dashboard draw fully clears the boot splash
static bool                   suspended      = false; // USB suspend: keep the OLED off and skip refreshes

// Switch to dashboard at 3000ms: stop the (holding) boot animation and start the
// periodic dashboard refresh. The one-shot full wipe is handled by
// display_task_kb() via the dashboard_init flag.
uint32_t refresh_callback(uint32_t trigger_time, void *cb_arg) {
    qp_stop_animation(anim_token);
    boot_done = true;
    display_task_kb();
    return 500;
}

void display_init_kb(void) {
    display = qp_sh1106_make_i2c_device(128, 32, 0x3c);
    qp_init(display, QP_ROTATION_90);
    font    = qp_load_font_mem(font_quinquefive);
    if (!display_init_user()) return;

    // Blank the physical GDDRAM first — qp_init turns the display on but
    // doesn't clear it, so on a soft reboot stale dashboard content would
    // bleed through under the animation's delta frames.
    qp_clear(display);
    qp_flush(display);

    // The last frame of the boot animation has a long (60s) delay baked into
    // the QGF, so it holds on the final frame without looping. The dashboard
    // takes over at 3000ms and stops the animation.
    anim_token = qp_animate(display, 0, 0, qp_load_image_mem(gfx_boot_anim));
    qp_flush(display);

    refresh_token = defer_exec(3000, refresh_callback, NULL);
}

__attribute__((weak)) bool display_init_user(void) { return true; }
void display_key_counter(void) {}
__attribute__((weak)) bool display_task_user(void) { return true; }

// Lock-LED indicators: three boxes (N/C/S) that fill white when active.
// Adapted from rev1 for the 32px-wide rotated panel.
static void draw_led_state(led_t state) {
    static const char *const labels[3] = {"N", "C", "S"};
    const bool               active[3] = {state.num_lock, state.caps_lock, state.scroll_lock};
    static const uint8_t     bx[3]     = {1, 11, 21};
    for (uint8_t i = 0; i < 3; i++) {
        uint8_t x = bx[i];
        qp_rect(display, x, 2, x + 8, 9, 0, 0, 255, active[i]);
        if (!active[i]) {
            qp_rect(display, x + 1, 3, x + 7, 8, 0, 0, 0, true);
        }
        qp_drawtext_recolor(display, x + 2, 3, font, labels[i],
                            0, 0, active[i] ? 0 : 255,
                            0, 0, active[i] ? 255 : 0);
    }
}

static void draw_dashboard(void) {
    char b[6];

    // Row 0: lock LEDs (filled boxes, white when active)
    draw_led_state(host_keyboard_led_state());

    // Row 1: layer
    uint8_t layer = get_highest_layer(layer_state);
    snprintf(b, sizeof(b), "L%u", layer);
    qp_drawtext(display, 2, 11, font, b);

    // Row 2: scan rate
    uint32_t rate = get_matrix_scan_rate();
    snprintf(b, sizeof(b), "%-5lu", (unsigned long)rate);
    qp_drawtext(display, 2, 20, font, b);

    // Row 3: RT + NKRO
    snprintf(b, sizeof(b), "%s %s",
             he_config.actuation_mode ? "RT" : "AP",
             keymap_config.nkro ? "6K" : "nk");
    qp_drawtext(display, 2, 29, font, b);
}

void display_task_kb(void) {
    if (!display_task_user()) return;
    // Block any dashboard drawing during the boot animation or while suspended.
    if (!boot_done || suspended) return;
    // The dashboard lives in the top-left corner (4 rows of 5px text at
    // y=2..34). Only clear that region so qp_flush ships ~160 bytes instead
    // of the full 512-byte framebuffer, keeping the main loop responsive.
    if (!dashboard_init) {
        qp_clear(display); // one-shot full clear to erase the boot splash
        dashboard_init = true;
    } else {
        qp_rect(display, 0, 0, 31, 39, 0, 0, 0, true);
    }
    draw_dashboard();
    qp_flush(display);
}

// Redraw the lock-LED row immediately when the host changes LED state, instead
// of waiting up to 500ms for the next dashboard tick.
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res && boot_done && !suspended) {
        qp_rect(display, 0, 0, 31, 10, 0, 0, 0, true);
        draw_led_state(led_state);
        qp_flush(display);
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    if (boot_done && !suspended) {
        display_task_kb();
    }
    return state;
}

// USB suspend (host off / asleep): power the OLED down so it doesn't stay lit,
// and gate refreshes. suspend_power_down_kb is called repeatedly while suspended,
// so only act on the transition.
void suspend_power_down_kb(void) {
    if (!suspended) {
        suspended = true;
        qp_power(display, false);
    }
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    suspended      = false;
    dashboard_init = false; // force a full clear/redraw after resume
    // Full re-init the display rather than just powering on: USB suspend can
    // leave the I2C peripheral / surface dirty-state in an inconsistent spot,
    // which makes qp_flush ship a full frame every task tick after resume and
    // crushes the matrix scan rate. qp_init re-inits the surface framebuffer
    // (zeroed, full dirty mark) and the SH1106 hardware, so the next flush is
    // a clean baseline instead of a corrupted one.
    qp_init(display, QP_ROTATION_90);
    qp_power(display, true);
    qp_clear(display);
    qp_flush(display);
    display_task_kb();
    suspend_wakeup_init_user();
}
