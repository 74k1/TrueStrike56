// Copyright 2026 74k1
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keymap_swiss_de.h"

// KEY OVERRIDES
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t backslash_key_override = ko_make_basic(MOD_MASK_SHIFT, CH_SLSH, CH_BSLS);

// this globally defines which key overrides are to be used
const key_override_t *key_overrides[] = {
    &delete_key_override,
    &backslash_key_override
};

// TAIKO COMBOS
const uint16_t PROGMEM escape_combo[] = {KC_TAB, CH_1, COMBO_END};
const uint16_t PROGMEM ae_combo[] = {KC_E, KC_A, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_E, KC_O, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_E, KC_U, COMBO_END};

combo_t key_combos[] = {
    COMBO(escape_combo, KC_ESC),
    COMBO(ae_combo, CH_ADIA),
    COMBO(oe_combo, CH_ODIA),
    COMBO(ue_combo, CH_UDIA)
};

// Snap Tap - bannable in CS
//const key_cancellation_t PROGMEM key_cancellation_list[] = {
//    // on key down
//    //       |    key to be released
//    //       |     |
//    [0] = {KC_D, KC_A},
//    [1] = {KC_A, KC_D},
//};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_4x6_4( // NORMAL
    // .----------------------------------------------------.       .----------------------------------------------------.
    // | ESC   | 1      | 2      | 3      | 4      | 5      |.-----.| 6     | 7      | 8      | 9      | 0      | <-     |
         KC_ESC,    CH_1,    CH_2,    CH_3,    CH_4,    CH_5,           CH_6,    CH_7,    CH_8,    CH_9,    CH_0, KC_BSPC,
    // |-------+--------+--------+--------+--------+--------||     ||-------+--------+--------+--------+--------+--------|
    // | TAB   | Q      | W      | E      | R      | T      ||     || Z     | U      | I      | O      | P      | ->     |
         KC_TAB,    CH_Q,    CH_W,    CH_E,    CH_R,    CH_T,           CH_Z,    CH_U,    CH_I,    CH_O,    CH_P,  KC_DEL,
    // |-------+--------+--------+--------+--------+--------||     ||-------+--------+--------+--------+--------+--------|
    // | LSFT  | A      | S      | D      | F      | G      |'-----'| H     | J      | K      | L      | /      | RSFT   |
        KC_LSFT,    CH_A,    CH_S,    CH_D,    CH_F,    CH_G,           CH_H,    CH_J,    CH_K,    CH_L, CH_SLSH, KC_RSFT,
    // |-------+--------+--------+--------+--------+--------+ .===. +-------+--------+--------+--------+--------+--------|
    // | LCTL  | Y      | X      | C      | V      | B      | '===' | N     | M      | ,      | .      | -      | ENTER  |
        KC_LCTL,    CH_Y,    CH_X,    CH_C,    CH_V,    CH_B,           CH_N,    CH_M, CH_COMM,  CH_DOT, CH_MINS,  KC_ENT,
    // '-------+--------+--------+--------+--------+------------+-----------+--------+--------+--------+--------+--------'
                      //| MOD    | LALT   | LAYER1 | SPACE      | ENTER     | LAYER2 | RALT   | N/A    |
                          KC_LGUI, KC_LALT,   MO(1),      KC_SPC,     KC_ENT,   MO(2), KC_RALT, XXXXXXX,
                      //'--------+--------+--------+------------+-----------+--------+--------+--------'

                      //                  Scroller:  MUTE   |
                      //                             
                                                     KC_MUTE
    ),
    [1] = LAYOUT_split_4x6_4( // FKEYS, ARROWS, MODS
    // .----------------------------------------------------.       .----------------------------------------------------.
    // |       | F1     | F2     | F3     | F4     | F5     |.-----.| F6    | F7     | F8     | F9     | F0     | <-     |
        CH_SECT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
    // |-------+--------+--------+--------+--------+--------||     ||-------+--------+--------+--------+--------+--------|
    // | TAB   | F11    | F12    | F13    | F14    | F15    ||     || F18   | F17    | F18    | F19    | F20    | ->     |
        _______,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,         KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20, _______,
    // |-------+--------+--------+--------+--------+--------||     ||-------+--------+--------+--------+--------+--------|
    // | LSFT  | CAPS   | PrScr  | INS    | UP     |        |'-----'| LEFT  | DOWN   | UP     | RIGHT  |        | RSFT   |
        _______, KC_CAPS, KC_PSCR, KC_INS,  KC_UP,   XXXXXXX,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______,
    // |-------+--------+--------+--------+--------+--------+ .===. +-------+--------+--------+--------+--------+--------|
    // | LCTL  |        |        | LEFT   | DOWN   | RIGHT  | '===' | HOME  | PGDN   | PGUP   | END    |        |        |
        _______, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT,        KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX,
    // '-------+--------+--------+--------+--------+------------+-----------+--------+--------+--------+--------+--------'
                      //| MOD    | LALT   | LAYER1 | SPACE      | ENTER     | LAYER3 | RALT   |        |
                          _______, _______, _______,     _______,    _______,   MO(3), _______, XXXXXXX,
                      //'--------+--------+--------+------------+-----------+--------+--------+--------'

                      //                  Scroller:  MUTE   |
                                                     _______
    ),
    [2] = LAYOUT_split_4x6_4( // SPECIAL
    // .----------------------------------------------------.       .----------------------------------------------------.
    // | ESC   | 1      | 2      | 3      | 4      | 5      |.-----.| 6     | 7      | 8      | 9      | 0      | <-     |
        _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
    // |-------+--------+--------+--------+--------+--------||     ||-------+--------+--------+--------+--------+--------|
    // | ~     | ^      | @      | #      | °      | $      ||     || `     | |      | '      | ?      | !      | ->     |
        CH_TILD, CH_CIRC, CH_AT,   CH_HASH, CH_DEG,  CH_DLR,          CH_GRV, CH_PIPE, CH_QUOT, CH_QUES, CH_EXLM, _______,
    // |-------+--------+--------+--------+--------+--------||     ||-------+--------+--------+--------+--------+--------|
    // | LSFT  | <      | [      | {      | (      | \      |'-----'| /     | )      | }      | ]      | >      | RSFT   |
        _______, CH_LABK, CH_LBRC, CH_LCBR, CH_LPRN, CH_BSLS,        CH_SLSH, CH_RPRN, CH_RCBR, CH_RBRC, CH_RABK, _______,
    // |-------+--------+--------+--------+--------+--------+ .===. +-------+--------+--------+--------+--------+--------|
    // | LCTL  |        |        | MUTE   | VOL DN | VOL UP | '===' | PRV   | PLY    | NXT    |        |        | ENTER  |
        _______, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU,        KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, _______,
    // '-------+--------+--------+--------+--------+------------+-----------+--------+--------+--------+--------+--------'
                      //| MOD    | LALT   | LAYER3 | SPACE      | ENTER     | LAYER2 | RALT   | N/A    |
                          _______, _______,   MO(3),     _______,    _______, _______, _______, XXXXXXX,
                      //'--------+--------+--------+------------+-----------+--------+--------+--------'

                      //                  Scroller:  MUTE   |
                                                     _______
    ),

    [3] = LAYOUT_split_4x6_4( // QMK
    // .----------------------------------------------------.       .----------------------------------------------------.
    // |       |        |        |        |        |        |.-----.|       |        |        |        |        |        |
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // |-------+--------+--------+--------+--------+--------||     ||-------+--------+--------+--------+--------+--------|
    // |       |        |        |        |        |        ||     ||       |        |        |        |        |        |
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // |-------+--------+--------+--------+--------+--------||     ||-------+--------+--------+--------+--------+--------|
    // | BOOT  |        |        |        |        |        |'-----'|       |        |        |        |        |        |
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // |-------+--------+--------+--------+--------+--------+ .===. +-------+--------+--------+--------+--------+--------|
    // |       |        |        |        |        |        | '===' |       |        |        |        |        |        |
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // '-------+--------+--------+--------+--------+------------+-----------+--------+--------+--------+--------+--------'
                      //| MOD    | LALT   | LAYER1 | SPACE      | ENTER     | LAYER2 | RALT   | N/A    |
                          XXXXXXX, XXXXXXX, _______,     _______,    _______, _______, XXXXXXX, XXXXXXX,
                      //'--------+--------+--------+------------+-----------+--------+--------+--------'

                      //                  Scroller:  MUTE   |
                                                     _______
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [2] = { ENCODER_CCW_CW(_______, _______) },
    [3] = { ENCODER_CCW_CW(_______, _______) },
};
