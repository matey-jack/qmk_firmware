#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "keymap_us_international_linux.h"

// Ubuntu shortcuts
#define UB_DESKL LGUI(KC_PGUP)
#define UB_DESKR LGUI(KC_PGDN)
#define UB_WINDL LSFT(LGUI(KC_PGUP))
#define UB_WINDR LSFT(LGUI(KC_PGDN))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
            LT(2,KC_ESC), KC_1, KC_2, KC_3, KC_4, KC_5,                     KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
            KC_TAB, KC_Q, KC_W, KC_B, KC_F, US_QUOT,                        KC_Z, KC_K, KC_U, KC_O, KC_P, KC_EQL,
            KC_LSFT, KC_A, KC_S, KC_D, KC_R, KC_G,                          KC_H, KC_N, KC_I, KC_L, KC_T, KC_RSFT,
            KC_LCTL, LT(1,KC_Y), KC_X, KC_C, KC_V, KC_SLSH, KC_LGUI,  MO(2), KC_J, KC_M, KC_COMM, KC_DOT, LT(1,KC_MINS), KC_NO,
                                            KC_LALT, KC_DEL, KC_SPC,  KC_ENT, KC_E, KC_RCTL
        ),
    [1] = LAYOUT(
            KC_NO, US_GRV, US_ACUT, US_SECT, US_EURO, US_CENT,              KC_NO, KC_PIPE, KC_LBRC, KC_RBRC, US_SS, KC_NO,
            KC_NO, KC_NO, LCTL(KC_LEFT), KC_UP, LCTL(KC_RGHT), KC_NO,       KC_NO, KC_BSLS, KC_LCBR, KC_RCBR, US_TILD, US_UDIA,
            KC_LSFT, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,            KC_NO, US_MUL, KC_LPRN, KC_RPRN, US_ODIA, KC_RSFT,
            KC_NO, KC_TRNS, KC_NO, KC_PGUP, KC_PGDN, KC_NO, KC_NO,   KC_NO, KC_NO, US_MICR, KC_SCLN, KC_COLN, KC_NO, US_ADIA,
                                            KC_NO, KC_BSPC, KC_ENT,  KC_NO, KC_NO, KC_NO
        ),
    [2] = LAYOUT(
            KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                         KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, EE_CLR,
            KC_NO, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO,                         KC_NO, RM_TOGG, RM_HUED, RM_SATD, RM_VALD, QK_BOOT,
            KC_LSFT, KC_MPRV, KC_MNXT, KC_NO, KC_NO, KC_NO,                     KC_NO, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, KC_NO,
            KC_NO, KC_NO, UB_WINDL, UB_DESKL, UB_DESKR, UB_WINDR, KC_NO, KC_TRNS, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSTP, KC_MPLY,
                                        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
        )
};



#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
