# PettingZoo
Code and Circuit Diagrams for giving Roomba's personality.
This is a fork from [https://github.com/chaudhuryB/PettingZoo](https://github.com/chaudhuryB/PettingZoo), with added support for the SPI audio boards below.
- Adafruit VS1053 Codec + MicroSD Breakout (v2.0): [https://www.adafruit.com/product/1381](https://www.adafruit.com/product/1381)
  - Subtitle: MP3/WAV/MIDI/OGG Play + Record
- SparkFund MP3 Player Shield (v15): [https://www.sparkfun.com/sparkfun-mp3-player-shield.html](https://www.sparkfun.com/sparkfun-mp3-player-shield.html)
  - dropped due to bad availability

# About
The [robotic petting zoo](https://www.roboticpettingzoo.com/) project was produced at the [SoBA Lab](http://www.soba-lab.com/), within the Psychology Department, at Bangor University. The technical requirement for the project was to control a robotic vacuum cleaner to display a certain personality and play a characteristics sound when it bumped into any objects as it went about doing the cleaning task. This document details how to go about doing this for anyone who wants to try to give their Roombas a personality.

* [RoboticPettingZoo.pdf](https://github.com/chaudhuryB/PettingZoo/blob/master/Robotic%20Petting%20Zoo.pdf)  : Contains more about the project, design and circuit diagram
* [roomba_pet](https://github.com/chaudhuryB/PettingZoo/tree/master/roomba_pet)             : Contains the code files for Arduino Uno Rev3 for controlling the Roomba
* [SDContents](https://github.com/chaudhuryB/PettingZoo/tree/master/SDContents)            : Contains sample config and sound file for two personalities (Angry and Apologetic) to go into the SD card
