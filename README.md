# ESP32_MultiModule_DCSBios
### A Wireless multi-module DCS-Bios button box based on ESP32 microcontroller.

----

#### 1. Introduction

This project has been started to experiment and test the interaction capabilities of DCS-Bios with the multi-module Radio button box that I was previously created.

___Keep this in mind, as this is an implementation specifically designed for this button box and may not work with yours.___

The initial implementation of the button box was based on the Raspberry Pi-Pico + ESP-01 pair. The data stream is obtained wirelessly from DCS-Bios, via the ESP-01, and then displayed on the screens (8 digits seven-segments + OLED), and the user interaction is provided through traditional HID button box interaction.

<p align="center">
<img src="/images/panel_radio1.jpg" alt="Multi-module Radio button box" width="300"/>
</p>

The button box implements:
* ***2 Radios*** with Frequency tuning knobs + AM/FM switch + Mode selector + Channel selector + Prog/Load button for each one.
* ***1 Radio selector switch*** *(R1/R2)*. It allows to share the encoders and buttons between the two radios selecting the the active radio.
* ***TACAN*** with tunning knobs + X/Y channel selector + Mode selector + ON/OFF switch
* ***ILS*** with tunning knobs + ON/OFF switch
* ***Brightness knob***

In total there are 53 different buttons, each one with different ways to interact with DCS in function of the current active module in DCS.

It should be taken into consideration that some components present in the button box do not exist in some DCS modules. And furthermore, some modules require different ways to do the same actions. By this reason it is no easy to create an universal button box.

----

#### 2. Project presentation

The current project is a first implementation that provides the interaction exclusively based on DCS-Bios avoiding the HID interface.

It receives and sends data completely wirelessly and is capable of managing several modules. Examples for the A-4E-C, F-5E-3 and VNAO-T45 are present in the source code folder. 

----

#### 3. Why this project

The use of HID devices allows users to easily interact with DCS. It is just required assign the controls to the corresponding buttons using the DCS interface. However, this is a unidirectional interaction, users are just only capable to send commands to DCS but they are not able to get and process any information. DCS-Bios is able to get data from the DCS modules and export their data out of DCS. Arduino DCS-Bios library allows the bi-directional communication, getting the data from DCS-Bios and providing commands to DCS.

The main issue in the original Arduino DCS-Bios implementations is the fact that the Arduino code is module dependent, it is not capable to interact with any other module that the initial for which it was programmed. It does not provide a multi-module management.

The main goal in the present project is to be capable of manage several modules easily. The main drawback to overcome is the Arduino UNO board memory limitation. Although it is possible to use any other Arduino flavour board as it is Arduino MEGA, there are many other microcontrollers options. Thus, the microcontroller selected in this project is the ESP32. This microcontroller has a big amount of memory, WiFi support, and much more CPU power than traditional Arduino boards. But what is really interesting is the WiFi capability of the ESP32 that allows to avoid the USB port, and then any wired connection with the PC.

Thus, the present project allows the user to:
  * Receive data from and send commands to DCS-Bios.
  * Manage several DCS modules that have DCS-Bios interface*.
  * Avoid the wired connection of the button-box via the USB port with the PC.
  * Allows the wireless interaction with DCS-Bios.

> \* It is required to have a DCS-Bios/Module interface. You can have some of them via the [DCS-Bios](https://github.com/dcs-bios) official github, or in the [DCS Fligh Panels](https://github.com/DCSFlightpanels/dcs-bios) DCS-Bios fork


---
ToDo: improve the documentation and some code stuff
