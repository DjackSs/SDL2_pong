# SDL2_pong

## Description

This project is an attempt to recreate the famous game from the 70s with the SDL2 library.

## Technologies

* C

### Features

* A single-player game mode similar to Atari's breakout game
* A duo game mode similar to Atari's pong game

## Setup

### Installation

- `git clone https://github.com/DjackSs/SDL2_pong.git`

### Play

run [pong.exe](/bin/pong.exe) and you are good to go.

### Code

* The project is pre-configured to compile with the GNU Compiler Collection for Windows (MinGW)
* The [SDL2 Library](https://www.libsdl.org/) is needed

#### Makefile

In the [makefile](/makefile):
* Change the includeSDL2 path to where the SDL2 header files are in your system (/include/SDL)
* Change the libSDL2 path to where the SDL2 libraries files are in your system (/lib)

By default, the SDL2 files are set up in the root of the project.

#### Cmake

When I will figure it out....

### Compiling

Run the commande `make` in the project's root to generat a pong.exe.


