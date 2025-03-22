#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "../../../../../quantum/keymap_extras/keymap_us_international_linux.h"
#include "us-ext-intl-mod.h"

// prev/next word shortcuts, works in almost all applications.
// (This helps avoid pressing Ctrl modifier in addition to the layer toggle.)
#define KC_PRWD  LCTL(KC_LEFT)
#define KC_NXWD  LCTL(KC_RGHT)

// layer toggles all have double duty.
#define L1_Y     LT(1, KC_Y)
#define L1_X     LT(1, KC_X)
#define L1_DOT   LT(1, KC_DOT)
#define L1_MINS  LT(1, KC_MINS)
#define L1_ENT   LT(1, KC_ENT)
#define L2_ESC   LT(2, KC_ESC)
#define L2_INS   LT(2, KC_INS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // standard keyboard layer
    [0] = LAYOUT(
            L2_ESC , KC_1, KC_2, KC_3, KC_4, KC_5   ,                     KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
            KC_TAB , KC_Q, KC_W, KC_B, KC_F, KC_QUOT,                     KC_Z, KC_K, KC_U, KC_O, KC_P, KC_PGUP,
            KC_LSFT, KC_A, KC_S, KC_D, KC_R, KC_G   ,                     KC_H, KC_N, KC_I, KC_L, KC_T, KC_RSFT,
            KC_LCTL, L1_Y, L1_X, KC_C, KC_V, KC_SLSH, KC_LGUI,    L2_INS, KC_J, KC_M, KC_COMM, L1_DOT, L1_MINS, KC_PGDN,
                                     KC_LALT, KC_DEL, KC_SPC ,    L1_ENT, KC_E, KC_RCTL
        ),
    // alternate character and navigation layer
    // we have US_TILD here, which is the 'live' key for programmers.
    // Dead tilde for accents can be obtained with Shift+US_GRV as on any other keyboard.
    // I just mention it, because this and capital ÄÖÜ are the only characters that need pressing both Shift and AltGr.
    [1] = LAYOUT(
            KC_NO  , KX_DGRV, KX_ACUT, US_SECT, US_EURO, US_CENT,                       KX_CIRC, KC_PIPE, KC_LBRC, KC_RBRC, US_IQUE, KC_DEL,
            KC_NO  , KC_NO  , KC_PRWD, KC_UP  , KC_NXWD, KC_GRV ,                       US_DEG , KC_LCBR, KX_LPRN, KX_RPRN, KC_RCBR, KC_TILD,
            KC_LSFT, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END ,                       US_MICR, US_SS  , US_UDIA, US_ODIA, US_ADIA, KC_RSFT,
			KC_LCTL, KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_BSLS, KC_LGUI,     KC_NO  , US_MUL , KC_EQL , KX_LT  , KX_GT  , KX_DASH, KC_NO,
                                                KC_LALT, KC_BSPC, KC_ENT ,     KC_SPC , KC_NO  , KC_RCTL
        ),
    // function layer, like on a laptop.
    // TODO: Add a one-shot-mod AltGr key, so we can access all characters from software layout AltGr, that don't have
    // a direct mapping in our firmware AltGr layer. (Meant for rare characters and as workaround for mapping bugs.)
    [2] = LAYOUT(
            KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                       KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , EE_CLR,
            KC_NO  , KC_F11 , KC_F12 , KC_NO  , KC_NO  , KC_NO  ,                       KC_NO  , RM_TOGG, RM_HUED, RM_SATD, RM_VALD, QK_BOOT,
            KC_LSFT, KC_MPRV, KC_MNXT, KC_NO  , KC_NO  , KC_NO  ,                       KC_NO  , RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, KC_NO  ,
			KC_LCTL, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_LGUI,     KC_NO  , KC_NO  , KC_MUTE, KC_VOLD, KC_VOLU, KC_MSTP, KC_MPLY,
                                                KC_LALT, KC_NO  , KC_NO  ,     KC_NO  , KC_NO  , KC_RCTL
        ),
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
