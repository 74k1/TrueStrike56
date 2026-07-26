# TrueStrike 56 (Rev 2) - Build Guide

This guide has been written by Tim <74k1>.

## Required

Choose between either a FR-4 Sandwich-Style Case or an Aluminium CNC'd Case.

| Name | Count | Notes |
| --- | --- | --- |
| [Main PCB](hw/rev2/pcb/TrueStrike56/Gerber) | x1 | |
| [Top Aluminium Case](hw/rev2/case/TrueStrike_Case_top_plate.obj) | x1 | For Aluminium Case! |
| [Bottom Aluminium Case](hw/rev2/case/TrueStrike_Case_bottom_plate.obj) | x1 | For Aluminium Case! |
| [Top Plate](hw/rev2/top-plate/) | x1 | For Sandwich-Style Case! |
| [Bottom Case](hw/rev2/bottom-plate/) | x1 | For Sandwich-Style Case! |
| RP2040 dev board with ProMicro compatible pinouts | x1 | You can get one from AliExpress. |
| 128x32 I2C OLED Screen | x1 | |
| EVQWGD001 Encoder | x1 | Get one while the stock still lasts! |
| M2x4mm bolts | x8 | For Aluminium Case! Preferably flat-headed |
| M2x4mm bolts | x16 | For Sandwich-Style Case! Preferably flat-headed |
| M2 7~8mm standoffs | x8 | For Sandwich-Style Case! Cannot have a larger diameter of 3.5mm! (The hexagonal ones won't work!) |
| Some 1mm thick Thermal Pads (not paste) | x1-2 | For Aluminium Case! It'll be used to "bind" the RP2040 with the Aluminium Case. |
| 1U Keycaps of your own choice | x54 | |
| 1.5U Keycaps of your own choice | x2 | |
| HE Switches of your own choice | x56 | |

## Ordering PCB & Case from JLC

### PCBA

I took a small shortcut by ordering the parts including "PCBA".

You can do so too by:

1. Zipping the main PCB folder

  - [Main PCB](hw/rev2/pcb/TrueStrike56/Gerber)

2. Upload the PCB to JLC's Standard PCB/PCBA for a quote and follow these settings:

  ![](/.github/res/rev2/build_guide/jlc_pcb_1.png)

3. Continue. You will eventually have to upload the [BOM](hw/rev2/TrueStrike56/production/bom.csv) and [Positions](hw/rev2/TrueStrike56/production/positions.csv) file.

  ![](/.github/res/rev2/build_guide/jlc_pcb_2.png)

4. Continue. The error only shows the missing RP2040, OLED and our Scrolling Encoder.

  ![](/.github/res/rev2/build_guide/jlc_pcb_3.png)

5. Hit the two boxes. Then search for missing parts:

  ![](/.github/res/rev2/build_guide/jlc_pcb_4.png)

6. Enter `74HC4051D,653-JSM` into the search field, and select the only part shown

  ![](/.github/res/rev2/build_guide/jlc_pcb_5.png)

7. Your final BOM should look like this:

  ![](/.github/res/rev2/build_guide/jlc_pcb_6.png)

8. On the next screen, you'll see some components misplaced / not rotated. (Zoomed in image for reference)

  ![](/.github/res/rev2/build_guide/jlc_pcb_7.png)

9. You'll want to select the following and then hit the rotate button twice.

  ![](/.github/res/rev2/build_guide/jlc_pcb_8.png)

10. That's it for the PCBA. With the correct Category, you can then save it to cart.

  ![](/.github/res/rev2/build_guide/jlc_pcb_9.png)

### Cases

Depending on whether it's the Sandwich-Style Case or the Aluminium Case, you either:

| Sandwich-Style Case | Aluminium Case |
| --- | --- |
| You upload the following files to the PCB Quote site.<br>Just keep the defaults / choose your own color. | You upload the following files to the CNC Quote site.<br>Feel free to adjust the finish to your liking. (In my case, I did Aluminium 6061, Bead Blasting + Anodizing, Dark Green, Matte, Tight Test Tolerance at +-0.10mm)<br><br>One note, you'll need to add the "Threads" service to the top half of the case. The technical drawing is attached. |
| You'll need to Zip these folders again:<br>- [Top Plate](hw/rev2/top-plate/Gerber)<br>- [Bottom Case](hw/rev2/bottom-plate/Gerber) |- [Aluminium Top](hw/rev2/case/TrueStrike_Case_top_plate.step)<br>- [Technical Drawing for Threads](hw/rev2/case/TrueStrike_Case_Technical_drawing.pdf)<br>- [Aluminium Bottom](hw/rev2/case/TrueStrike_Case_bottom_plate.step) |

## Assembly

Assembly is quite straightforward. A few hints based on what to do first though:

1. Make sure to flash either the default firmware onto the RP2040 board or your own, BEFORE you solder it to the PCB, as the RP2040 RST buttons on the RP2040 Pro Micro board won't be accessible after soldering.
2. If Aluminium Case: Cut and adjust the Thermal Pads onto the Board before soldering. (between PCB and RP2040 Pro Micro)
3. Add EVQWGD001 and OLED screen to the PCB (it'd make sense to put electrical tape between the RP2040 PCB and the OLED Screen)
  - NOTE: The EVQWGD001 hole on the PCB is very tight. You'll have to bend the pins a little bit to make it fit very snug. As a tip: start with the plastic part, then the pins.
4. Add your Switches to the top plate
5. If Aluminium Case: Cut and adjust the rest of the Thermal Pads between the bottom plate and the PCB.
6. Afterwards, it's pretty self-explanatory from here on out.

## Questions

Should you have questions, feel free to contact either of us.
I currently don't accept commissions to build a keyboard for you.
