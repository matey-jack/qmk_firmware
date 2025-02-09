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
#define L2_ESC   LT(2, KC_ESC)
#define L2_INS   LT(2, KC_INS)

// CC for custom code: those are translating from the Ergodox layout (which has the additional ß key).
// To make it work, ß actually needs to be mapped to a base key -- yet another case of making the present task more complicated because of an anticipated need :worry:
enum my_keycodes {
  CC_6 = SAFE_RANGE,
  CC_9,
  CC_0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // standard keyboard layer
    [0] = LAYOUT(
            L2_ESC , KC_1, KC_2, KC_3, KC_4, KC_5   ,                     KC_6, KC_7, KC_8, CC_9, CC_0, KC_BSPC,
            KC_TAB , KC_Q, KC_W, KC_B, KC_F, US_QUOT,                     KC_Z, KC_K, KC_U, KC_O, KC_P, KC_PGUP,
            KC_LSFT, KC_A, KC_S, KC_D, KC_R, KC_G   ,                     KC_H, KC_N, KC_I, KC_L, KC_T, KC_RSFT,
            KC_LCTL, L1_Y, KC_X, KC_C, KC_V, CC_SLSH, KC_LGUI,   L2_INS , KC_J, KC_M, KC_COMM, KC_DOT, L1_MINS, KC_PGDN,
                                             KC_LALT, KC_DEL ,   KC_SPC , KC_ENT, KC_E, KC_RCTL
        ),
    // alternate character and navigation layer
    // we have US_TILD here, which is the 'live' key for programmers.
    // Dead tilde for accents can be obtained with Shift+US_GRV as on any other keyboard.
    // I just mention it, because this and äöü are the only characters that need pressing both Shift and AltGr.
    [1] = LAYOUT(
            KC_NO  , US_DGRV, US_ACUT, US_SECT, US_EURO, US_CENT,                       US_DCIR, KX_PIPE, KC_LBRC, KC_RBRC, US_IQUE, US_SS  ,
            KC_NO  , KC_NO  , KC_PRWD, KC_UP  , KC_NXWD, US_GRV ,                       US_DEG , KX_BSLS, KC_LCBR, KC_RCBR, US_TILD, US_UDIA,
            KC_LSFT, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END ,                       KC_NO  , US_MUL , KC_LPRN, KC_RPRN, US_ODIA, KC_RSFT,
			KC_LCTL, KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_LGUI,     KC_TRNS, US_MICR, KC_EQL , KC_SCLN, KC_COLN, KX_DASH, US_ADIA,
                                                KC_NO  , KC_BSPC, KC_ENT ,     KC_NO  , KC_NO  , KC_RCTL
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

void add_or_del_key(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_key(keycode);
    } else {
        del_key(keycode);
    }
    send_keyboard_report();
}

// This assumes that +=? are on Shift+90ß in the software layout,
// and moves them to Shift+690.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t shifted = (get_mods() & MOD_MASK_SHIFT);
    switch (keycode) {
        case CC_6:
            add_or_del_key(shifted ? KC_9  : KC_6, record);
            return false;
        case CC_9:
            add_or_del_key(shifted ? KC_0  : KC_9, record);
            return false;
        case CC_0:
            add_or_del_key(shifted ? KX_SS : KC_0, record);
            return false;
        default:
            return true;
    }
}

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
