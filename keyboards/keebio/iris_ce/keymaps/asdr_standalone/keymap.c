/*
 *   This layout aims to behave as closely as possible to 'asdr_bespoke', without needing to have a custom "support"
 *   software layout installed on the computer.  It targets standard US ANSI and US ext. int'l as software layouts.

 The obvious advantage of this is that the layout works on any computer including Chromebooks and Android devices!
 I am actually looking forward to use the nice and portable Iris keyboard with an Android tablet to create a really
 neat and ergonomic travel setup. Remember that a tablet screen can be positioned independently of the keyboard, so it's
 much easier to create an ergonomic setup than when using a laptop's built-in keyboard!

 Some necessary limitations are:
  - no nice extra Unicode characters like – (n-dash)
  - ' and " are dead keys on Winwdows US ext int'l, because they are mapped as in the Linux version of US ext int'l
     But they work fine on Windows when using US ANSI. Basically, on Windows you can work okay by switching to US ANSI
     to type English text or programming stuff, and switch to US ext. int'l to type German texts. (Then the extra tap
     on the space key to create ' and " will only be there in German mode.)

 One other limitation that I am still working on minimizing:
  - Since I want the Shift+character mappings to work exactly as in the 'bespoke' layout, I created a separate layer
    that is activated by the Shift keys. This means that Shift key press/release will not be sent to the computer any
    more. We thus need to include some other ways to make actions like Shift+Click or Shift+Navigation keys possible.
  - Most of this works in rather intuitive ways (Shift+PgUp/Dn is 100% the same), other cases have some limitations
    (AltGr+Shift+CursorKeys requires AltGr to be pressed first to get into the right layer. On the bespoke layout, you
    can press both at the same time or in any order.)
  - And to get Shift+Click, you need to use AltGr+Shift+Click (until someone thinks of a nicer shortcut,
    maybe a separate tap/hold key just for that use-case...

 *
 */

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
// This can be used both for expected behavior of cursor and navigation keys.
// It can also be used to send plain Shift to the computer to combine it with mouse clicks.
// (Remember that when pressing AltGr+Shift AltGr is only a layer switch, so that the computer sees only Shift.)
// Unfortunately, since the LT(,) macro only supports basic keycodes, we always have to press first AltGr then Shift to do selections.
// With Shift already pressed, the two AltGr keys become simple Y and _ keys. (Which is not the case when using pure Shift...)

// Macros!
enum custom_keycodes {
    MX_VERS = SAFE_RANGE,
    MX_DASH,
    MX_QUOT,
    MX_DQUO,
    MX_TGM ,  // toggle quote mode
};

enum quote_mode {
    // this works for the standard US keyboard on all platforms,
    // but on Google Pixel 4a it even works with US ext. intl.
    // This is great and all OS' should do it like this!
    // And I am happy that I have independently invented this in my bespoke/support layout :-D
    QUOTE_MODE_ANSI,
    // This is for US ext intl Linux as in QMK's header file.
    QUOTE_MODE_LINUX,
    // This is probably a bug in Samsungs Galaxy Tab S9 FE+ (and who knows how many other similar devices).
    // It's here since I can workaround it quickly and have no hopes of the bug getting fixed.
    QUOTE_MODE_SAMSUNG,
};

const char *const quote_mode_names[] = {
    [QUOTE_MODE_ANSI] = "ANSI",
    [QUOTE_MODE_LINUX] = "Linux",
    [QUOTE_MODE_SAMSUNG] = "Samsung",
};

int current_quote_mode = QUOTE_MODE_ANSI;

// previous and next word cursor navigation
// (This helps avoid pressing Ctrl modifier in addition to the layer toggle.)
#define KC_PRWD  LCTL(KC_LEFT)
#define KC_NXWD  LCTL(KC_RGHT)

#define KL_SHFT  MO(L_SHIFT)
#define L2_Y     LT(L_ALTGR, KC_Y)
#define L2_X     LT(L_ALTGR, KC_X)
#define L2_MINS  LT(L_ALTGR, KC_MINS)
#define L2_ENT   LT(L_ALTGR, KC_ENT)
#define L3_ESC   LT(L_FN, KC_ESC)
#define L3_INS   LT(L_FN, KC_INS)

// One-shot-mod AltGr key, so we can access all characters from software layout AltGr, that don't have
// a direct mapping in our firmware AltGr layer. (Meant for rare characters and as workaround for mapping bugs.)
#define OS_ALGR  OSM(MOD_RALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // standard keyboard layer
    [L_BASE] = LAYOUT(
            L3_ESC , KC_1, KC_2, KC_3, KC_4, KC_5   ,                     KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
            KC_TAB , KC_Q, KC_W, KC_B, KC_F, MX_QUOT,                     KC_Z, KC_K, KC_U, KC_O, KC_P, KC_PGUP,
            KL_SHFT, KC_A, KC_S, KC_D, KC_R, KC_G   ,                     KC_H, KC_N, KC_I, KC_L, KC_T, KL_SHFT,
            KC_LCTL, L2_Y, L2_X, KC_C, KC_V, KC_SLSH, KC_LGUI,   L3_INS , KC_J, KC_M, KC_COMM, KC_DOT, L2_MINS, KC_PGDN,
                                             KC_LALT, KC_DEL ,   KC_SPC , L2_ENT, KC_E, KC_RCTL
        ),
    // slightly modified shift layer
    [L_SHIFT] = LAYOUT(
              L3_ESC  , S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5   ),                        US_PLUS, S(KC_7), S(KC_8), KC_EQL , KC_QUES, S(KC_BSPC),
            S(KC_TAB ), S(KC_Q), S(KC_W), S(KC_B), S(KC_F),   MX_DQUO ,                        S(KC_Z), S(KC_K), S(KC_U), S(KC_O), S(KC_P), S(KC_PGUP),
              KC_LSFT , S(KC_A), S(KC_S), S(KC_D), S(KC_R), S(KC_G   ),                        S(KC_H), S(KC_N), S(KC_I), S(KC_L), S(KC_T),   KC_RSFT ,
            S(KC_LCTL), S(KC_Y), S(KC_X), S(KC_C), S(KC_V),   KC_BSLS , S(KC_LGUI),   L3_INS , S(KC_J), S(KC_M), KC_SCLN, KC_COLN, KC_UNDS, S(KC_PGDN),
                                                S(KC_LALT), S(KC_DEL ), S(KC_SPC ), S(KC_ENT), S(KC_E), S(KC_RCTL)
        ),
    // alternate character and navigation layer
    // we have US_TILD here, which is the 'live' key for programmers.
    // Dead tilde for accents can be obtained with Shift+US_DGRV aka AltGr+Shift+2.
    // Same trick works for diaresis accent: AltGr+Shift+1. (When the device is on US ANSI, this is the fallback to get a double quote!)
    [L_ALTGR] = LAYOUT(
            KC_NO  , US_DGRV, US_ACUT, US_SECT, US_EURO, US_CENT,                       US_CIRC, KC_PIPE, KC_LBRC, KC_RBRC, US_IQUE, KC_DEL ,
            KC_NO  , KC_NO  , KC_PRWD, KC_UP  , KC_NXWD, US_GRV ,                       US_DEG , KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, US_TILD,
            KC_LSFT, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END ,                       US_MICR, US_SS  , US_UDIA, US_ODIA, US_ADIA, KC_RSFT,
			KC_LCTL, KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_BSLS, KC_LGUI,     KC_NO  , US_MUL , KC_EQL , KC_LT  , KC_GT  , MX_DASH, KC_NO,
                                                KC_LALT, KC_BSPC, KC_ENT ,     KC_SPC , KC_NO  , KC_RCTL
        ),
    // function layer, like on a laptop.
    [L_FN] = LAYOUT(
            KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                       KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , EE_CLR,
            MX_VERS, KC_F11 , KC_F12 , KC_NO  , KC_NO  , MX_TGM ,                       KC_NO  , RM_TOGG, RM_HUED, RM_SATD, RM_VALD, QK_BOOT,
            KC_LSFT, KC_MPRV, KC_MNXT, KC_NO  , KC_NO  , KC_NO  ,                       KC_NO  , RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, KC_NO  ,
			KC_LCTL, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_LGUI,     KC_TRNS, KC_NO  , KC_MUTE, KC_VOLD, KC_VOLU, KC_MSTP, KC_MPLY,
                                                KC_LALT, KC_NO  , KC_NO  ,     OS_ALGR, KC_NO  , KC_RCTL
        )
};


// 3 ms still had some dropped letters.
const int SEND_STRING_DELAY_MS = 10;

void toggle_quote_mode(void) {
    switch (current_quote_mode) {
        case QUOTE_MODE_ANSI:
            current_quote_mode = QUOTE_MODE_LINUX;
            break;
        case QUOTE_MODE_LINUX:
            current_quote_mode = QUOTE_MODE_SAMSUNG;
            break;
        case QUOTE_MODE_SAMSUNG:
            current_quote_mode = QUOTE_MODE_LINUX;
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MX_QUOT:
            // We only handle the press event.
            if (!record->event.pressed) return false;
            switch (current_quote_mode) {
                case QUOTE_MODE_ANSI:
                    send_string("'");
                    return false;
                case QUOTE_MODE_LINUX:
                    send_string(SS_RALT("'"));
                    return false;
                case QUOTE_MODE_SAMSUNG:
                    // it's a dead key with only one mapping, namely the key itself.
                    send_string_with_delay(SS_RALT("''"), SEND_STRING_DELAY_MS);
                    return false;
            }
        case MX_DQUO:
            // We only handle the press event.
            if (!record->event.pressed) return false;
            switch (current_quote_mode) {
                case QUOTE_MODE_ANSI:
                    send_string("\"");
                    return false;
                case QUOTE_MODE_LINUX:
                case QUOTE_MODE_SAMSUNG:
                    send_string(SS_RALT("\""));
                    return false;
            }
        // US_ACUT only works in Linux, but on Android we can make it using the on-screen keyboard if needed.
        // We might also need different handling for KC_GRV, but I think that if variants are different,
        // they are just swapping US_GRV and US_DGRV (i.e. the mapping of the base key and its AltGr character).
        // Both are accessible in the layout and users can just swap them mentally.
        case MX_VERS:
            if (record->event.pressed) {
                send_string_with_delay("Layout ASDR_NILT standalone, rev03-quote-modes, ", SEND_STRING_DELAY_MS);
                send_string_with_delay(__DATE__, SEND_STRING_DELAY_MS);
                send_string_with_delay("\nQuote mode: ", SEND_STRING_DELAY_MS);
                send_string_with_delay(quote_mode_names[current_quote_mode], SEND_STRING_DELAY_MS);
                send_string_with_delay("\n", SEND_STRING_DELAY_MS);
            } else {
                // when keycode is released
            }
            return false;
        case MX_TGM:
            if (record->event.pressed) {
                toggle_quote_mode();
            } else {
                // when keycode is released
            }
            return false;
        case MX_DASH:
            if (record->event.pressed) {
                // TODO
            } else {
            }
            return false;
    }
    // all other cases to be handled by QMK.
    return true;
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
