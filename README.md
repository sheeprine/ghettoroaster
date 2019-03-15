# ghettoroaster #
Firmware and schematics for a network controlled coffee roaster.

## Disclaimer ##

The information provided in this repository is provided as is. Roasters and
popcorn poppers are electric components connected to main power. You should
take your precautions while working on them. If you don't know what you are
doing please refrain from modifying this kind of hardware as it as enough power
to kill you.

## Goals ##

Produce a cheap and easy to build roast controller. This build doesn't need any
bit of solder and is architectured around standard and easily available
components.

## Hardware used ##

For a simple heater controlled popper which information shown on an LCD the
cost is around 10$ excluding the popper.

Here is the list of materials needed:

### ESP8266 / nodemcu (±2$) ###

The microcontroller used is an ESP8266 which is cheap and easily available. If
you want an easy setup just go for a nodemcu that will provide every external
components needed for the ESP8266 to work.

### MAX6675 (± 2$ a piece) ###

This project use K junction thermocouple as they are cheap and available
everywhere. A MAX6675 controller is used to handle hardware specific
configuration. You will need at least one for the bean temperature.

### i2c 16 x 2 LCD (± 1.5$) ###

This part is optional, and only needed if you want to see roast information in
real time. And monitor more closely what's going on.

### Zero cross SSR (±4$) ###

This part is used to control the heater of your popper. If you only want to
monitor your roast process it's not needed.
