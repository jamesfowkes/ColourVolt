# ColourVolt

## A project to display if a voltage is within a given voltage range

### People

The PCB was re-designed by Matt Little from Renewable Energy Innovation.

The software was by Matt Little and James Fowkes

Contact:
www.re-innovation.co.uk
matt@re-innovation.co.uk


### Features

This unit measures voltage and displays it as a colour on an RGB LED.
It also reads out the voltage on the serial port when asked via its unique ID.
It can be calibrated (via a serial command) and can have its ID changed (via serial command)

The board measures its own power supply voltage.
The board has a single RGB LED. It will be red if the voltage is under-range, blue if over-range, green if within range.
This board is designed for use in pedal-powered equipment, although other application are of course possible.

To set the range two potentiometers are used (see 'Setup' section).

The project uses LLAP for communications. For more information, see [the LLAP reference at Ciseco](http://openmicros.org/index.php/articles/85-llap-lightweight-local-automation-protocol/297-llap-reference)
### Setup

**The serial format for all commands is 4800 8N1**
**The serial connector has a standard FTDI pinout**

**For the following instructions, XX represents the LLAP ID of the device.**
####To give the board a unique ID:####

* Ensure the unit is powered off.
* Plug in a serial cable.
* The unit will send 'aXXSTARTED'
* Send 'aXXCHDEVIDAA', where XX is the current ID and AA is the new ID.
* The unit will send 'aAASTARTED', where AA is the new ID.

####To calibrate the board to a known voltage:####

* Apply 10V to the power input
* Plug in a serial cable.
* Send 'aXXCAL'.
* The unit will calibrate (takes about 2 seconds).
* Send 'aXXV?', where XX is the device ID.
* The unit should return 'aXX10.00V' or similar, showing a correct calibration to 10V.

####To set the voltage range (unit must be calibrated):####

* Plug in a serial cable.
* Send 'aXXSETUP'.
* The unit go into setup mode and will being sending messages every 1.5 seconds.
* Messages starting with 'aXXSP' are the ideal setpoint voltage.
* Messages starting with 'aXXRNG' are the allowable voltage range.
* For example 'aXXSP12.35V' and 'aXXRNG1.53V' mean that the acceptable voltage is 12.35V +/- 1.53V.
* Turn the two potentiometers until the desired setpoint and range are set. The potentiometers are both 10-turn.
* Send 'aXXSETUP' to turn off setup mode.

###To read current settings###
* Plug in a serial cable.
* Sending 'aXXV?"' will return the current "live" voltage reading
* Sending 'aXXHT?"' will return the high threshold
* Sending 'aXXLT?"' will return the low threshold
* Sending 'aXXSP?"' will return the setpoint
* Sending 'aXXRNG?"' will return the allowable variation from the setpoint

### Notes

The microcontroller used is an ATTINY84. When programming the board, you must ensure that:

* The CVKDIV fuse bit is unprogrammed (1). This is to allow the software serial library to run at sufficient speed.
* The BODLEVEL fuse bits are set to 100. This is to ensure that the EEPROM is not corrupted in low-voltage situations.
* The EESAVE fuse bit is programmed (0). This ensures that the device ID and calibration are preserved over a programming cycle.

The unit will ship with the fuses correctly set. If they need to be restore, the following avrdude command can be used:

`avrdude -p t84 -c {your_isp_programmer} -b 19200 -U lfuse:w:0xe2:m -U hfuse:w:0xd4:m -U efuse:w:0xff:m`
