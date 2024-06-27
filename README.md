# Project Glove

The Glove project comprises a glove (manipulator) and a machine (which is controlled).

## Features

The glove serves as the server to which the machine is connected. The glove is equipped with a flex sensor that alters resistance when it is bent. We record the voltage that falls on this sensor on the ADC. We then convert the range from (1800-600) to (0-255) so that we can control the machine with a shim.
All numbers less than 100 are converted to 0, as a shim of this nature will not be able to start the motors. Additionally, this number is used to control the LEDs fed to the shim. LEDs on the board are necessary for more convenient control of the glove. The middle LED blinks when communication between the machine and the glove is established and outputs the machine shim values to the LEDs.

## Screenshots

![What does the glove look like](https://i.imgur.com/Eao1KAn.png)

## Authors

- [@ioiparzival](https://github.com/ioiparzival)
