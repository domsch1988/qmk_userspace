#!/bin/bash

# This is a script to link the local Keyboard Profile into the qmk_firmware Project
# This assumes the default qmk setup with the qmk repository being found in ~/qmk_firmware/

rm -rf $HOME/qmk_firmware/keyboards/splitkb/kyria/keymaps/domsch1988
ln -s "$HOME/Daten/01 - Configuration/05 - Hardware/01 - Keyboard/domsch1988" $HOME/qmk_firmware/keyboards/splitkb/kyria/keymaps/domsch1988
