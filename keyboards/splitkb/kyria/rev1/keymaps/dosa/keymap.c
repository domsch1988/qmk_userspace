#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "sendstring_german.h"

enum layers {
    QWE = 0,
    SYM,
    NUM,
    NAV,
    FUN,
    NUL
};

#define ME_SPC MEH_T(KC_SPC)
#define LE_SFT SFT_T(QK_LEAD)
#define LA_FUN LT(FUN, KC_ENT)
#define LA_SYM LT(SYM, KC_BSPC)
#define LA_NUM LT(NUM, KC_TAB)
#define LA_NAV LT(NAV, KC_ESC)
#define WI_CPY C(KC_C)
#define WI_PST C(KC_V)
#define WI_CUT C(KC_X)
#define WI_UND C(KC_Z)
#define AP_1 G(KC_1)
#define AP_2 G(KC_2)
#define AP_3 G(KC_3)
#define AP_4 G(KC_4)
#define AP_5 G(KC_5)
#define AP_6 G(KC_6)
#define AP_7 G(KC_7)
#define AP_8 G(KC_8)
#define AP_9 G(KC_9)
#define AP_10 G(KC_0)
#define MO_Z CTL_T(KC_Z)
#define MO_X ALT_T(KC_X)
#define MO_CTL CTL_T(DE_UNDS)
#define MO_ALT ALT_T(DE_DOT)
#define MO_HYP ALL_T(DE_COMM)
#define MO_CTLA CTL_T(KC_Y)
#define MO_ALTA ALT_T(KC_B)
#define MO_HYPA ALL_T(KC_W)
#define BR_TABL RCS(KC_TAB)
#define BR_TABR C(KC_TAB)

enum custom_keycodes {
    SH_LEAD = SAFE_RANGE, //normal shift, oneshot layer 2 on tap
    //other macros,
};
 
 
bool key_pressed = false;    //variable used to check if a key is pressed while SH_LAY2 is held
uint16_t SH_LEAD_TIMER = 0;  //declare a timer variable to track hold time for SH_LAY2
 
bool process_record_user(uint16_t keycode, keyrecord_t *record) {   
    if (record->event.pressed)
        key_pressed = true;  //if any key is pressed, set key_pressed to true
    
    switch (keycode) {
        case SH_LEAD:
            if (record->event.pressed) {       //when SH_LAY2 is pressed
                register_code(KC_LSFT);        //  press left shift
                key_pressed = false;           //  set key_pressed to false  
                SH_LEAD_TIMER = timer_read();  //  mark the time SH_LAY2 was pressed
            } else {                           //when SH_LAY2 is released
                unregister_code(KC_LSFT);      //  release left shift
                if (key_pressed) break;  //  if another key was pressed while shift was held, exit and do not use one shot layer
                
                if (timer_elapsed(SH_LEAD_TIMER) < TAPPING_TERM) {  //if SH_LAY2 was held for less than TAPPING_TERM (default 200ms)
                    leader_start();     //  necessary for oneshots in macros.  don't touch this line
                }
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWE] = LAYOUT(
     _______ , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                           KC_Y  ,   KC_U ,  KC_I ,   KC_O ,  KC_P , _______,
     _______ , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                           KC_H  ,   KC_J ,  KC_K ,   KC_L ,DE_MINS, _______,
     _______ , MO_Z ,  MO_X   ,  KC_C  ,   KC_V ,   KC_B ,  _______, _______,     _______, _______,  KC_N  ,   KC_M , MO_HYP, MO_ALT , MO_CTL, _______,
                                _______, _______, LA_NAV , SH_LEAD , LA_NUM ,     LA_FUN , ME_SPC , LA_SYM , KC_LGUI, _______
    ),
    [SYM] = LAYOUT(
     _______ , DE_LABK, DE_RABK, DE_LCBR, DE_RCBR, DE_DLR ,                                     DE_ASTR, DE_UDIA, DE_TILD, DE_ODIA, DE_EURO, _______,
     _______ , DE_ADIA,  DE_SS , DE_LPRN, DE_RPRN, DE_PERC,                                     DE_PIPE, DE_QUES, DE_EXLM, DE_EQL , DE_AT  , _______,
     _______ , DE_BLSH, DE_SLSH, DE_LBRC, DE_RBRC, DE_AMPR, _______, _______, _______, _______, DE_HASH, DE_DQUO, DE_QUOT, DE_CIRC, DE_GRV , _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [NUM] = LAYOUT(
      _______, BR_TABL, _______, _______, BR_TABR, _______,                                    DE_PLUS,  KC_7  ,  KC_8  ,  KC_9  ,  DE_SLSH, _______,
      _______, KC_WBAK, _______, KC_WREF, KC_WFWD, _______,                                    DE_MINS,  KC_4  ,  KC_5  ,  KC_6  ,  _______, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, DE_ASTR,  KC_1  ,  KC_2  ,  KC_3  ,   KC_DOT, _______,
                                 _______, _______, _______,_______, _______, _______, _______, KC_0   , _______, _______
    ),
    [FUN] = LAYOUT(
      _______,  KC_F12,  KC_F7 ,  KC_F8 ,  KC_F9 , _______,                                    _______, _______, _______, _______,  _______, _______,
      _______,  KC_F11,  KC_F4 ,  KC_F5 ,  KC_F6 , _______,                                    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,  _______, _______,
      _______,  KC_F10,  KC_F1 ,  KC_F2 ,  KC_F3 , _______,_______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
    [NAV] = LAYOUT(
      _______, AP_1   , AP_2   , AP_3   , AP_4   , AP_5   ,                                    AP_6   , AP_7   , AP_8   , AP_9   ,  AP_10  , _______,
      _______, WI_UND , WI_CUT , WI_CPY , WI_PST , KC_DEL ,                                    KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT,  _______, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END ,  _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
    [NUL] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

};

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_F, KC_MINS)) {
        // Leader, f => Types the below string
        tap_code16(MEH(KC_Z));
    } else if (leader_sequence_three_keys(KC_T, KC_P, KC_E)) {
        // Leader, d, d => Ctrl+A, Ctrl+C
        SEND_STRING("REDACTED");
    } else if (leader_sequence_three_keys(KC_T, KC_P, KC_F)) {
        // Leader, d, d => Ctrl+A, Ctrl+C
        SEND_STRING("REDACTED");
    } else if (leader_sequence_three_keys(KC_T, KC_E, KC_S)) {
        // Leader, d, d => Ctrl+A, Ctrl+C
        SEND_STRING("dominik@schlack.net");
    } else if (leader_sequence_three_keys(KC_T, KC_E, KC_G)) {
        // Leader, d, d => Ctrl+A, Ctrl+C
        SEND_STRING("dominik.schlack@gmail.com");
    } else if (leader_sequence_three_keys(KC_T, KC_E, KC_F)) {
        // Leader, d, d => Ctrl+A, Ctrl+C
        SEND_STRING("dominik.schlack@frequentis.com");
    }
}



#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case QWE:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case FUN:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case NUM:
                oled_write_P(PSTR("Numbers\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif
