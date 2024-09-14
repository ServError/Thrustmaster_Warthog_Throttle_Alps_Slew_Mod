# Firmware

The firmware was developed in Atmel/Microchip studio, and targets the ATTINY441 MCU. Originally, the project started on the ATTINY44A, but its multipurpose serial interface used for I2C didn't play well with the Warthog's I2C so I went with a pin compatible sister chip in order to avoid having to redesign my PCB.

## Flashing

If you just want to flash the MCU and get up and running, grab the hex file in the [Release](TM%20Warthog%20Alps%20Slew%20Mod/Release/) folder and flash it using your method of choice (one example provided below in [Windows Flashing Example](#windows-flashing-example-courtesy-of-stic). I used a USBTinyISP and a DIP8 clip on the appropriate pins(rewired by jumping between the two ribbon cables) while supplying power over the main cable, but there are many flashers and connection methods at your disposal.

## Debugging

A debug header is present next to the main header and requires wires or a connector with 1.00mm spacing.

## Features

The firmware is focused around extremely low power consumption. The I2C peripheral handles communication while the processor is mostly asleep. It wakes up only to poll the joystick once between I2C polls, as well as to provide necessary I2C servicing.


# Windows Flashing Example (Courtesy of StiC)

### Programming the ATtiny 441 with a USBASP and AVRDUDE

First you’ll need a USBASP and a chip clip or socket to connect it to the ATtiny 441. They can be found on Amazon fairly cheaply.

https://www.amazon.ca/USBASP-Programmer-ATMEGA8-ATMEGA128-Support/dp/B07KK1CDQC

https://tinyurl.com/SOIC-Clip

![image](https://github.com/user-attachments/assets/53ca7b8b-0a70-48da-b8f7-63a80fe6a965)
USB ASP - bottom left  
Soic16 to dip16 socket - top left  
Soic16 clip - right


Next you’ll need AVRDUDE.

https://github.com/avrdudes/avrdude/releases

Extract it to a folder in the root directory. C:\AVRDUDE for example.


Open the [TM Warthog Alps Slew Mod/Release](TM%20Warthog%20Alps%20Slew%20Mod/Release) folder and open "TM Warthog Alps Slew Mod.hex". Download it using the 'Download raw file' button at the top right of the viewer.

Change the name of the downloaded file to something without spaces. “slew.hex” for example.
Move/copy it to the same folder as AVRDUDE.

 
Connect the VCC, RST, MOSI, MISO, SCK and GND from the USB ASP to the corresponding pins on the clip or socket. Use the Dark Blue bubbles (ISP interface) in the image to help locate the pins. Double check the connections before plugging in the USB ASP. Depending on the type of clip, a multimeter may be required to know which pin each wire is connected to. A socket would make this easier, but they can be more expensive.

![image](https://github.com/user-attachments/assets/4fa44972-8805-4819-aa2e-6a0a88a9dbef)

Place the chip within the jaws of the clip. You may be able to place the chip pins down and just pick it up with the clip. Make sure the chip is in the right position and orientation. The small dot at the top of the chip indicates pin 1.

Plug the USB ASP into a USB port.


In Windows go to the search field in the lower left and type CMD. Select Command Prompt from the list.

![image](https://github.com/user-attachments/assets/65e5533e-d7ca-4eae-8a04-60a44d4b989c)

In the command prompt window, type, or copy and paste, (without quotation marks) “cd\”, and hit Enter.
You should see C:\>

![image](https://github.com/user-attachments/assets/c26777bc-4c5f-4125-8398-e4911cfea454)

Type, “cd avrdude” if you followed my suggestion above.
You should see C:\AVRDUDE> 

![image](https://github.com/user-attachments/assets/93c02c81-3433-4ffe-b098-ca89ba346167)

Finally, type, “avrdude -c usbasp -p t441 -U flash:w:slew.hex” 
If you changed the hex file name to something else, use that instead of slew.

![image](https://github.com/user-attachments/assets/8b8955c1-6bef-460a-885e-268e93385306)

Hit Enter. Hopefully everything worked and no error messages appeared.


To program more, just put a new chip in the clip and tap the Up arrow on the keyboard and hit Enter. This will  repeat the last command in the Command Prompt window. 

