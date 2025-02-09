#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "keymap_us_international_linux.h"

enum layer_names {
    L_BASE,
    L_SHIFT,
    L_ALTGR,
    L_FN,
};
// "Shift" and "AltGr" keys in this layout are layer switches, thus send nothing to the computer.
// But the Shift key on the AltGr and Fn layers is mapped to a normal Shift.
// This can be used both for expected behavior of cursor and navigation keys
// (except PgUp/PgDn which aren't nav keys on the AltGr layer. TODO: we should make them Nav keys on the Fn layer!)
// It can also be used to send plain Shift to the computer to combine it with mouse clicks.
// (Remember that when pressing AltGr+Shift AltGr is only a layer switch, so that the computer sees only Shift.)
// Unfortunately, since the LT(,) macro only supports basic keycodes, we always have to press first AltGr then Shift to do selections.
// With Shift already pressed, the two AltGr keys become simple Y and _ keys. (Which is not the case when using pure Shift...)


// TODO: this will have to be a Macro
#define KC_DASH  S(ALGR(US_MINS))

// previous and next word cursor navigation
#define KC_PRWD  LCTL(KC_LEFT)
#define KC_NXWD  LCTL(KC_RGHT)

#define KL_SHFT  MO(L_SHIFT)
#define L2_Y     LT(2, KC_Y)
#define L2_MINS  LT(2, KC_MINS)
#define L2_ENT   LT(2, KC_ENT)
#define L3_ESC   LT(3, KC_ESC)
#define L3_INS   LT(3, KC_INS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // standard keyboard layer
    [L_BASE] = LAYOUT(
            L2_ESC , KC_1, KC_2, KC_3, KC_4, KC_5   ,                     KC_6, KC_7, KC_8, CC_9, CC_0, KC_BSPC,
            KC_TAB , KC_Q, KC_W, KC_B, KC_F, US_QUOT,                     KC_Z, KC_K, KC_U, KC_O, KC_P, KC_PGUP,
            KL_SHFT, KC_A, KC_S, KC_D, KC_R, KC_G   ,                     KC_H, KC_N, KC_I, KC_L, KC_T, KL_SHFT,
            KC_LCTL, L1_Y, KC_X, KC_C, KC_V, CC_SLSH, KC_LGUI,   L2_INS , KC_J, KC_M, KC_COMM, KC_DOT, L1_MINS, KC_PGDN,
                                             KC_LALT, KC_DEL ,   KC_SPC , L2_ENT, KC_E, KC_RCTL
        ),
    // slightly modified shift layer
    [L_SHIFT] = LAYOUT(
              L2_ESC  , S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5   ),                        US_PLUS, S(KC_7), S(KC_8), KC_EQL , KC_QUES, S(KC_BSPC),
            S(KC_TAB ), S(KC_Q), S(KC_W), S(KC_B), S(KC_F), S(US_QUOT),                        S(KC_Z), S(KC_K), S(KC_U), S(KC_O), S(KC_P), S(KC_PGUP),
              KC_LSFT , S(KC_A), S(KC_S), S(KC_D), S(KC_R), S(KC_G   ),                        S(KC_H), S(KC_N), S(KC_I), S(KC_L), S(KC_T),   KC_RSFT ,
            S(KC_LCTL), S(KC_Y), S(KC_X), S(KC_C), S(KC_V),   KC_BSLS , S(KC_LGUI),   L2_INS , S(KC_J), S(KC_M), KC_SCLN, KC_COLN, KC_UNDS, S(KC_PGDN),
                                                S(KC_LALT), S(KC_DEL ), S(KC_SPC ), S(KC_ENT), S(KC_E), S(KC_RCTL)
        ),
    // alternate character and navigation layer
    [L_ALTGR] = LAYOUT(
            KC_NO  , US_GRV , US_ACUT, US_SECT, US_EURO, US_CENT,                       KC_NO  , KC_PIPE, KC_LBRC, KC_RBRC, US_IQUE, US_SS  ,
            KC_NO  , KC_NO  , KC_PRWD, KC_UP  , KC_NXWD, KC_NO  ,                       KC_NO  , KC_BSLS, KC_LCBR, KC_RCBR, US_TILD, US_UDIA,
            KC_LSFT, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END ,                       KC_NO  , US_MUL , KC_LPRN, KC_RPRN, US_ODIA, KC_RSFT,
			KC_LCTL, KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_LGUI,     KC_TRNS, US_MICR, KC_EQL , KC_SCLN, KC_COLN, KC_DASH, US_ADIA,
                                                KC_NO  , KC_BSPC, KC_ENT ,     KC_NO  , KC_NO  , KC_RCTL
        ),
    // function layer, like on a laptop.
    [L_FN] = LAYOUT(
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
