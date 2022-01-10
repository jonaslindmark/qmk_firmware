#!/bin/sh

set -eux
dfu-programmer atmega32u4 erase --force
dfu-programmer atmega32u4 flash .build/lily58_rev1_lindmark.hex
dfu-programmer atmega32u4 reset
