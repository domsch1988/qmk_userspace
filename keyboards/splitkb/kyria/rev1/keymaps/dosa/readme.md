# Kyria rev1 – keymap `dosa`

Personal keymap for a splitkb Kyria rev1 (Elite-C, ATmega32u4).
The computer is set to the **German (QWERTZ)** layout, so the keymap uses QMK's `DE_*` keycodes.
Watch out: the plain `KC_Y` and `KC_Z` keycodes come out swapped (`KC_Z` types "y").

## Building

`qmk.json` in the repo root sets the build target to `splitkb/kyria/rev1/base` with keymap `dosa`.

```sh
# from the repo root
qmk compile -kb splitkb/kyria/rev1/base -km dosa

# no qmk CLI installed? nix can provide it:
nix-shell -p qmk --run "qmk compile -kb splitkb/kyria/rev1/base -km dosa"
```

The firmware has to fit in 28 672 bytes, and the build prints how much is used.

## Secrets (passwords typed by Leader sequences)

Some Leader sequences type passwords. **The passwords are not in this repo.**
They are kept in a separate header file on your computer and compiled in at build time.

### How it works

1. `rules.mk` adds a folder to the compiler's include path:
   ```make
   SECRETS_DIR ?= $(HOME)/.config/qmk
   EXTRAINCDIRS += $(SECRETS_DIR)
   ```
2. `keymap.c` includes `secrets.h` only if it exists:
   ```c
   #if __has_include("secrets.h")
   #    include "secrets.h"
   #endif
   ```
3. Each password sequence in `leader_end_user()` is wrapped in `#ifdef SECRET_…`.
   **If `secrets.h` is missing, the build still works.** Those sequences just do nothing.

### Setting it up on a new machine

Create `~/.config/qmk/secrets.h`:

```c
#pragma once

#define SECRET_TPE "first password"   // Leader, t, p, e
#define SECRET_TPF "second password"  // Leader, t, p, f
```

Then make it readable only by you and rebuild:

```sh
chmod 600 ~/.config/qmk/secrets.h
qmk compile -kb splitkb/kyria/rev1/base -km dosa
```

To keep the file somewhere else, point `SECRETS_DIR` at that folder. The path must not contain spaces:

```sh
qmk compile -kb splitkb/kyria/rev1/base -km dosa -e SECRETS_DIR=/path/to/folder
```

### Checking that the secrets were compiled in

Compare the firmware size with and without the file: the build with secrets is a bit larger.
Or test it on the keyboard: open a text editor and type Leader, t, p, e.

### Adding another secret

1. Add a macro to `secrets.h`, e.g. `#define SECRET_TPX "…"`.
2. Add a matching branch to `leader_end_user()` in `keymap.c`. Keep it inside the `if / else if` chain:
   ```c
   #ifdef SECRET_TPX
       } else if (leader_sequence_three_keys(KC_T, KC_P, KC_X)) {
           SEND_STRING(SECRET_TPX);
   #endif
   ```

### Rules

- **Never commit `secrets.h`.** `.gitignore` ignores it as a safety net, but keep it out of the repo anyway.
- SEND_STRING can only type characters on the German layout table (plain ASCII).
  Umlauts or `€` in a password won't come out right.
- The built firmware (`*.hex`, and `.build/` inside qmk_firmware) **contains the passwords**, stored as hex-encoded bytes in the file.
  `*.hex` is gitignored. Don't share firmware files from a build that included secrets.

## Leader sequences

Leader is `SH_LEAD`, the middle of the three left thumb keys you use (between Esc/NAV and Tab/NUM).
Tap it for Leader, hold it for Shift.

| Sequence | Action |
|---|---|
| `f` `-` | Meh+Y (global hotkey) |
| `t` `p` `e` | types `SECRET_TPE` (if defined) |
| `t` `p` `f` | types `SECRET_TPF` (if defined) |
| `t` `e` `s` | personal email |
| `t` `e` `g` | Gmail address |
| `t` `e` `f` | work email |
