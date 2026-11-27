OLED_ENABLE = yes
ENCODER_ENABLE = no       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
LEADER_ENABLE = yes

# Private strings (passwords) are kept outside the repo in $(SECRETS_DIR)/secrets.h.
# Override with: qmk compile -e SECRETS_DIR=/some/dir   (path must not contain spaces)
# If the file is missing, the build still works; the secret macros are just left out.
SECRETS_DIR ?= $(HOME)/.config/qmk
EXTRAINCDIRS += $(SECRETS_DIR)
