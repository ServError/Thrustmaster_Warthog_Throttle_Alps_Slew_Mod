# PCB

The PCB was designed in KiCAD and all project files are available in this repository for your tweaking pleasure.

## Ordering

For US based people, I recommend [OSH Park](https://oshpark.com/shared_projects/TJxoezw8) which can provide 3 boards for $4 to your door (which is insane!). Others will want to download the zip file from the [gerber_out](gerber_out/) folder and provide it to their PCB printing service of choice. It's possible that you'll need to download the KiCAD project and tweak the gerber settings if your printing service has any issues with the provided zip.

## Bill of Materials

| Part          | Quantity | Example Link |
| ------------- |:--------:| -----:|
| PCB           | 1        | [link](https://oshpark.com/shared_projects/TJxoezw8) |
| ATTINY441     | 1        | [link](https://www.mouser.com/ProductDetail/556-ATTINY441-SSU) |
| 100nF cap     | 1        | [link](https://www.mouser.com/ProductDetail/187-CL21B104KACNNNC) |
| 10k Ohm res   | 1        | [link](https://www.mouser.com/ProductDetail/603-RC0805FR-0710KL) |
| Joystick      | 1        | [link](https://www.mouser.com/ProductDetail/688-RKJXV122400R) |
| 1.6x4mm screw | 6        | [link](https://www.aliexpress.com/item/32968483467.html) |
| 15cm 5P cable | 1        | [link](https://www.aliexpress.com/item/32979005732.html) |
| 5P 1.25mm Header | 1        | [link](https://www.aliexpress.com/item/1005003115054198.html) |

If using the example link for the header, select the 'DIP' variety (they mean thru-hole, but oh well).

## Assembly

It's perfectly possible to construct the entire board with a soldering iron, but is certainly more convenient to install the microcontroller and passives using hot air.

If your PCB was delivered with excess material near the header side, I'd recommend filing it down for a cleaner fit.
