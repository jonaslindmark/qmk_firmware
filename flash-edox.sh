#!/bin/sh

set -eux
dfu-programmer atmega32u4 erase --force
dfu-programmer atmega32u4 flash .build/ergodox_ez_lindmark.hex
dfu-programmer atmega32u4 reset



