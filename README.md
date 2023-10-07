# OpenServo

This repository started as a clone from the `OpenServo` project https://github.com/ginge/OpenServo
and is a continuation of this open source project. The goal is to produce and manufacture a
V3-PCB, configure and modify a running firmware and create an Arduino library for accessing
OpenServos over I2C.

## OpenServo Hardware

The `OpenServo-Hardware` is cloned from https://github.com/ginge/OpenServo/tree/master/OpenServo/V3-PCB
and striped to a single board due to cost reduction for production with JLCPCB. The Gerber files for
this board are found in the file `V3-Single-PCB-Gerber.zip`.

## OpenServo Firmware

The `OpenServo-Firmware` is clonee from https://github.com/ginge/OpenServo/tree/master/OpenServo/AVR_OpenServo_V3-dev
and customized to my needs, bug fixing and cleanup.

## OpenServo Testclient

The `OpenServo-Testclient` is a test client for the `OpenServo Firmware`.
Due to a lack of documentation some things have to be rediscovered and tested.

## OpenServo Arduino Library

The `OpenServo-Arduino-Library` is still to be developed. It will implement an Arduino Library
for accessing an `OpenServo`.

# License

Copyright (c) 2023 by Andreas Trappmann.

MIT license, check LICENSE file for more information.

All text above must be included in any redistribution.

# Release Notes:

Version 1.0 - 04.10.2023

	* Initial Version
