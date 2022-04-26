# TetrisC

A simple Tetris implemented in C for a university project. Tested on Ubuntu 18.04 LTS.

![screenshot](/img/game.png?raw=true)

---------------------------------------------------------------------------------------------------------

## Requirements

*   libncurses5 (`sudo apt-get install ncurses-dev` to install on Ubuntu 18.04 LTS);

*   Check (`sudo apt-get install check` to install on Ubuntu 18.04 LTS);

*   make (`sudo apt-get install make` to install on Ubuntu 18.04 LTS);

*   CMake (`sudo apt-get -y install cmake` to install on Ubuntu 18.04 LTS);

*   Doxygen (`sudo apt-get install doxygen` to install on Ubuntu 18.04 LTS).

---------------------------------------------------------------------------------------------------------

## Installation

Clone or download the repository and type the following commands in the root folder:

```mkdir build```

```cd build```

```cmake ..```

```make```

To build the documentation, type `doxygen` in the root folder.

---------------------------------------------------------------------------------------------------------

## Usage

To run the unit tests, type `./bin/check_block` in the root folder.

To run the game, type `./bin/TetrisC` in the root folder.

---------------------------------------------------------------------------------------------------------

## Contact

luca.dellalib@gmail.com

---------------------------------------------------------------------------------------------------------
