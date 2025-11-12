#include "keycodes.h"
#include "modifiers.h"

/*
  We separate several categories of key types:
    - basic keycodes, aka USB standard keycodes. Those include characters with various language-specific subtypes, modifiers, and others.
    - USB keycodes with modifier bits set. (In case of Shift and AltGr modifiers, their subtype (letter or punctuation or other symbol) depends on the host's national keymap.
      In case of other modifiers, the meaning depends on the OS or application.)
    - QMK keycodes are split into the coarse categories:
        - layer toggles (all kinds: TO, OSL, LT, etc.)
        - lighting controls (this is separate, because the key types are made for the RGB matrix. Whoever uses the keytypes might want to control the matrix.)
        - fundamental controls (like QK_BOOT, QK_RESET, etc.)
        - others (left for future expansion)

    Note that the categories USB_other and OMK_other can be used as intermediate values before more fine-grained classification happens.
    There is no general "unknown" category, so we can always rely on the highest bit of the byte to distinguish USB keycodes from QMK keycodes.

    To allow a coarse classification, the highest bit of a byte is used to distinguish USB keycodes (highest bit 0) from QMK keycodes (highest bit 1).
    For a finer classification within USB keycodes, the second highest bit is used to distinguish character input keys (second highest bit 0) from other USB keycodes (second highest bit 1).
*/
enum KEY_COLOR_TYPE {
    /*
        USB Keycodes first, highest bit always set to 0.

        Starting with the character input keys, where the second highest bit is also 0.
    */
    // This color is important to locate accented or non-latin letters on higher layers.
    KEY_COLOR_LETTER = 0x00,

    // Nice touch for the base layer when there is a number row. Important for character discovery when there isn't.
    KEY_COLOR_NUMBER,

    // Maybe we should distinguish between prose punctuation and technical symbols?
    KEY_COLOR_PUNCTUATION,

    // Currency symbols and units like %. My feeling is that & and / still count as punctuation.
    // Maybe * and + and = could count as numeric operators. Although it's weird, since - and / are punctuation.
    KEY_COLOR_SYMBOL,

    // "dead key", not used with US ANSI, but important to highlight it with a separate color in other national keymaps.
    KEY_COLOR_COMBING_ACCENT,

    // a character key with either Shift or AltGr modifier bit set.
    // note that this is a fallback type used only when the character can't be classified using a national keymap.
    KEY_COLOR_MODIFIED_CHARACTER,

    // used when the character type hasn't been classified yet.
    KEY_COLOR_OTHER_CHARACTER,

    /*
        Now all the non-character USB keycodes. Second highest bit is 1.
    */
    // Shift, Ctrl, Alt, GUI
    KEY_COLOR_MODIFIER = 0x40,

    // arrows are special because their inverted T shape hints at what this color means.
    KEY_COLOR_ARROW,

    // other nav keys
    KEY_COLOR_NAVIGATION,

    // F-keys.
    KEY_COLOR_FUNCTION,

    // volume up/down, mute, play/pause, etc.
    KEY_COLOR_MEDIA_CONTROL,

    // any combination of modifiers with any key (except the "modified character" keys above).
    KEY_COLOR_MODIFIED_USB_KEY,

    // everything else sent to the host via USB.
    KEY_COLOR_USB_OTHER,

    /*
        QMK Keycodes here, they all have the highest bit (of a byte) set.
    */
    // AltGr and Fn and the magic accent-combining layer and the Windows layer
    // may the one-shot layer should have a different color... but we can do that via a direct keycode rule.
    KEY_COLOR_LAYER_TOGGLE = 0x80,

    // RM_*
    KEY_COLOR_RGB_CONTROL,

    // QK_BOOT, QK_RESET, etc.
    KEY_COLOR_QMK_CONTROL,

    // other QMK keycodes (important to distinguish those from keycodes sent to the host!)
    KEY_COLOR_QMK_OTHER,

    // unmapped keys (KC_NO or KC_TRNS)
    KEY_COLOR_UNMAPPED,
};

// Note that checking for a right modifier excludes the left one, but checking for the left one, includes both left and right.
#define HAS_RIGHT_ALT_MOD(keycode) (((keycode) >> 8) & MOD_RALT != 0)
#define HAS_SHIFT_MOD(keycode) (((keycode) >> 8) & MOD_LSFT != 0)
#define HAS_CTRL_OR_GUI_MOD(keycode) ((((keycode) >> 8) & (MOD_LCTL | MOD_LGUI)) != 0)
#define HAS_LEFT_ALT_MOD(keycode) (((keycode) >> 8) & 0x10 == 0) || (((keycode) >> 8) & MOD_LALT != 0)

// The national keymap on the host OS can change which keycode maps to which character, but it won't mix non-characters with characters.
// So this function should be generically correct at least for all the Latin-, Greek-, and Cyrillic-based keymaps.
bool is_character_keycode(uint8_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINUS ... KC_SLSH:
        case KC_KP_SLASH ... KC_KP_PLUS:
        case KC_KP_1 ... KC_NONUS_BACKSLASH:
            return true;
        default:
            return false;
    }
}

// This is the basic US ANSI classification...
// It's a separate function so that we can later plug in other national keymaps.
enum KEY_COLOR_TYPE classify_unmodified_character(uint8_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            return KEY_COLOR_LETTER;
        case KC_1 ... KC_0:
            return KEY_COLOR_NUMBER;
        case KC_MINUS:
        case KC_COMMA:
        case KC_DOT:
        case KC_QUOTE:
        case KC_SEMICOLON:
        case KC_SLASH:
            return KEY_COLOR_PUNCTUATION;
        default:
            return KEY_COLOR_SYMBOL;
    }
}

enum KEY_COLOR_TYPE classify_basic_keycode(uint8_t keycode) {
    if (is_character_keycode(keycode)) {
        return classify_unmodified_character(keycode);
    } else {
        switch (keycode) {
            case KC_LCTL ... KC_RGUI:
            case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
                return KEY_COLOR_MODIFIER;

            case KC_LEFT:
            case KC_RIGHT:
            case KC_UP:
            case KC_DOWN:
                return KEY_COLOR_ARROW;

            // TODO: custom nav keys with Ctrl?
            case KC_HOME:
            case KC_END:
            case KC_PGUP:
            case KC_PGDN:
                return KEY_COLOR_NAVIGATION;

            case KC_F1 ... KC_F12:
                return KEY_COLOR_FUNCTION;

            default:
                return KEY_COLOR_USB_OTHER;
        }
    }
}

// Very coarse classification, not even correct for US ANSI (since !? are punctuation characters).
enum KEY_COLOR_TYPE get_shifted_key_type(uint8_t keycode) {
    switch (classify_basic_keycode(keycode)) {
        case KEY_COLOR_LETTER:
            return KEY_COLOR_LETTER;
        case KEY_COLOR_NUMBER:
        case KEY_COLOR_PUNCTUATION:
        case KEY_COLOR_SYMBOL:
            return KEY_COLOR_MODIFIED_CHARACTER;
        default:
            return KEY_COLOR_MODIFIED_USB_KEY;
    }
}

enum KEY_COLOR_TYPE get_type(uint16_t keycode) {
    // handle this before "basic", because the QMK macro mistakingly includes those.
    if (keycode <= KC_TRANSPARENT) {
        return KEY_COLOR_UNMAPPED;
    }
    if (IS_QK_BASIC(keycode)) {
        return classify_basic_keycode(keycode & 0xFF);
    }
    if (IS_QK_MODS(keycode)) {
        if (HAS_CTRL_OR_GUI_MOD(keycode) || HAS_LEFT_ALT_MOD(keycode)) {
            return KEY_COLOR_MODIFIED_USB_KEY;
        }
        if (HAS_SHIFT_MOD(keycode) || HAS_RIGHT_ALT_MOD(keycode)) {
            return KEY_COLOR_MODIFIED_USB_KEY;
        }
        // by exclusion, the modifier must be Shift or AltGr or both.
        return get_shifted_key_type(keycode & 0xFF);
    }

    switch (keycode) {
        case QUANTUM_KEYCODE_RANGE:
            return KEY_COLOR_QMK_CONTROL;

        // this is numerically in the middle of the layer toggle keycodes, so we need to check it first.
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            // this is technically wrong, since it doesn't send anything to the host, but for lighting purposes it should have the color of a modifier.
            return KEY_COLOR_MODIFIER;

        case QK_LAYER_TAP ... QK_PERSISTENT_DEF_LAYER_MAX:
            return KEY_COLOR_LAYER_TOGGLE;

        case QK_RGB_MATRIX_ON ... QK_RGB_MATRIX_SPEED_DOWN:
            return KEY_COLOR_RGB_CONTROL;

        default:
            return KEY_COLOR_QMK_OTHER;
    }
}
