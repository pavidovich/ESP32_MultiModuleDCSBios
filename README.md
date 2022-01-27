# ESP32_MultiModule_DCSBios
### A Wireless multi-module DCS-Bios button box based on ESP32 microcontroller.

This project has been started in order to provide interaction between DCS and the multi-module Radio button box that I was previously created.
<p align="center">
<img src="/images/panel_radio1.jpg" alt="Multi-module Radio button box" width="300"/>
</p>

This button box implements:
* ***2 Radios*** with Frequency tuning knobs + AM/FM switch + Mode selector + Channel selector + Prog/Load button for each one.
* ***1 Radio selector switch*** *(R1/R2)*. It allows to share the encoders and buttons between the two radios selecting the the active radio.
* ***TACAN*** with tunning knobs + X/Y channel selector + Mode selector + ON/OFF switch
* ***ILS*** with tunning knobs + ON/OFF switch
* ***Brightness knob***

In total there are 53 different buttons, each one with different ways to interact with DCS in function of the current active module in DCS.

It should be taken into consideration that some components present in the button box do not exist in some DCS modules. And furthermore, some modules require different ways to do the same actions. By this reason it is no easy to create an universal button box.

The current project is just a first implementation to provide the required interaction based exclusively on DCS-Bios.

The modules profiles are based on those present in the [DCS Flight Panels](https://github.com/DCSFlightpanels)

---
ToDo: improve the documentation and some code stuff
