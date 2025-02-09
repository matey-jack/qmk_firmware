#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "keymap_us_international_linux.h"
#include "us-ext-intl-mod.h"

#define KC_PRWD  LCTL(KC_LEFT)
#define KC_NXWD  LCTL(KC_RGHT)

#define L1_Y     LT(1, KC_Y)
#define L1_MINS  LT(1, KC_MINS)
#define L1_ENT   LT(1, KC_ENT)
#define L2_ESC   LT(2, KC_ESC)
#define L2_INS   LT(2, KC_INS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // standard keyboard layer
    [0] = LAYOUT(
            L2_ESC , KC_1, KC_2, KC_3, KC_4, KC_5   ,                     KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
            KC_TAB , KC_Q, KC_W, KC_B, KC_F, US_QUOT,                     KC_Z, KC_K, KC_U, KC_O, KC_P, KC_PGUP,
            KC_LSFT, KC_A, KC_S, KC_D, KC_R, KC_G   ,                     KC_H, KC_N, KC_I, KC_L, KC_T, KC_RSFT,
            KC_LCTL, L1_Y, KC_X, KC_C, KC_V, KC_SLSH, KC_LGUI,    L2_INS, KC_J, KC_M, KC_COMM, KC_DOT, L1_MINS, KC_PGDN,
                                     KC_LALT, KC_DEL, KC_SPC ,   L1_ENT, KC_E, KC_RCTL
        ),
    // alternate character and navigation layer
    // we have US_TILD here, which is the 'live' key for programmers.
    // Dead tilde for accents can be obtained with Shift+US_GRV as on any other keyboard.
    // I just mention it, because this and capital ÄÖÜ are the only characters that need pressing both Shift and AltGr.
    [1] = LAYOUT(
            KC_NO  , KX_DGRV, KX_ACUT, US_SECT, US_EURO, US_CENT,                       US_DCIR, KC_PIPE, KC_LBRC, KC_RBRC, US_IQUE, US_SS  ,
            KC_NO  , KC_NO  , KC_PRWD, KC_UP  , KC_NXWD, KC_GRV ,                       US_DEG , KC_BSLS, KC_LCBR, KC_RCBR, KC_TILD, US_UDIA,
            KC_LSFT, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END ,                       KC_NO  , US_MUL , KC_LPRN, KC_RPRN, US_ODIA, KC_RSFT,
			KC_LCTL, KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_LGUI,     KC_TRNS, US_MICR, KC_EQL , KX_LT  , KX_GT  , KX_DASH, US_ADIA,
                                                KC_NO  , KC_BSPC, KC_ENT ,     KC_SPC , KC_NO  , KC_RCTL
        ),
    // function layer, like on a laptop.
    [2] = LAYOUT(
            KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                       KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , EE_CLR,
            KC_NO  , KC_F11 , KC_F12 , KC_NO  , KC_NO  , KC_NO  ,                       KC_NO  , RM_TOGG, RM_HUED, RM_SATD, RM_VALD, QK_BOOT,
            KC_LSFT, KC_MPRV, KC_MNXT, KC_NO  , KC_NO  , KC_NO  ,                       KC_NO  , RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, KC_NO  ,
			KC_LCTL, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_LGUI,     KC_TRNS, KC_NO  , KC_MUTE, KC_VOLD, KC_VOLU, KC_MSTP, KC_MPLY,
                                                KC_NO  , KC_NO  , KC_NO  ,     KC_NO  , KC_NO  , KC_RCTL
        )
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
