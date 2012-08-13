# To use this on Debian/Ubuntu you need to install the arduino-core package.
# To use this elsewhere you're on your own.
# This has only been tested with the version of the makefile that comes with arduino-mk v0.8.
# Some earlier versions are incompatible with the variables set below and need a different
# set of variables.

ARDUINO_DIR = /usr/share/arduino
TARGET = chronospec
BOARD_TAG = uno
ARDUINO_PORT = /dev/ttyACM*

include /usr/share/arduino/Arduino.mk
