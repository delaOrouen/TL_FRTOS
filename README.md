## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Controls](#controls)

## General info
This project is an RTOS implementation of a traffic light using a developement board and a couple push buttons.
	
## Technologies
Project is created with:
* GNU ARM Embedded Toolchain v10.3-2021 
* STM32F407VG Discovery Kit
* STM32CUBE IDE v1.8.0
* STM32CUBEMX v6.4.0
* stlink (package) v1.7.0
* ncurses-compat-libs v6.2-8.20210508
	
## Setup
Note: these steps are intended for use on Fedora Linux computer and have been tested on Fedora 35. 
1. To run this project, download this project from GitHub.  
2. Download and install STM32CUBE IDE and STM32CUBEMX.
3. Install st-link by running the following command:
```
$ sudo dnf install stlink
```
4. Follow the tutorial of "Learn embedded systems with George" to install the ARM Embedded Toolchain. (The link is found below.)
5. Install the dependencies of the ARM Embedded Toolchain by running the following command:
```
$ sudo dnf install ncurses-compat-libs
```
6. Wire two push buttons between the 3V GPIO and GND GPIO on the Discovery Kit Board. Connect a wire between from the Ground side of the buttons to PE0 and PE1 on 
the Discovery Board. 
6. Connect a usb-cable between CN1 on the Discovery Board and your computer. 
7. Change dictory in the terminal to the directory containing this project. 
8. The project should already be built, but for good measure, run the following commands. 
```
$ make clean
$ make
```
9. Install the program onto your board with the following command.
```
$ st-flash write ./build/*.bin 0x8000000
```

## Controls
To start the traffic light, press and hold the button connected to PE0. This will trigger the FSM to flash a red LED on the Discovery Board, then a green LED will flash.
Pressing and holding the button connected to PE1 will  trigger the FSM to flash a red LED for a second, then a yellow LED for a second
before switching to a red LED for another second.

