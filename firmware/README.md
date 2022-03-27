# Firmware

The firmware was developed in Atmel/Microchip studio, and targets the ATTINY441 MCU. Originally, the project started on the ATTINY44A, but its multipurpose serial interface used for I2C didn't play well with the Warthog's I2C so I went with a pin compatible sister chip in order to avoid having to redesign my PCB.

## Flashing

If you just want to flash the MCU and get up and running, grab the hex file in the [Release](TM Warthog Alps Slew Mod/Release/) folder and flash it using your method of choice. I used a USBTinyISP and a DIP8 clip on the appropriate pins(rewired by jumping between the two ribbon cables) while supplying power over the main cable, but there are many flashers and connection methods at your disposal.

## Debugging

A debug header is present next to the main header and requires wires or a connector with 1.00mm spacing.

## Features

The firmware is focused around extremely low power consumption. The I2C peripheral handles communication while the processor is mostly asleep. It wakes up only to poll the joystick once between I2C polls, as well as to provide necessary I2C servicing.