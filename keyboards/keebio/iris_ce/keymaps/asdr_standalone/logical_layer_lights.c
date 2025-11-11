#include "rgb_matrix.h"
#include "color.h"

enum lll_mode {
    LLL_MODE_OFF,

    // Only uses backlights when another layer than base is active.
    // (Those are also active in the two modes below.)
    LLL_MODE_LAYERS_ONLY,

    // Discreet lights on the base layer: only layer toggles have a different color.
    LLL_MODE_NIGHT,

    // Full colors on the base layer (which helps to see the meaning of the colors).
    LLL_MODE_EXPLANTORY,
} lll_mode_t;

static enum lll_mode current_lll_mode = LLL_MODE_LAYERS_ONLY;
// static uint8_t lll_brightness = 255; // TODO: after making this adjustable, save/load from EEPROM.
static bool LLL_TEMPORARY_SHOW_BASE_LAYER_COLORS = false;

void rgb_matrix_set_hsv_color(uint8_t index, uint8_t h, uint8_t s, uint8_t v) {
    hsv_t hsv = {h, s, v};
    hsv.v = (hsv.v * (uint16_t) rgb_matrix_config.hsv.v) / 255;
    rgb_t rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

// This function is only to reset the temporary state.
layer_state_t layer_state_set_user(layer_state_t state) {
    LLL_TEMPORARY_SHOW_BASE_LAYER_COLORS = false;
    return state;
}

void toggle_lll_mode(void) {
    // initialize RGB matrix and disable animations on every toggle, since it could have been toggled separately.
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_NONE);
    switch (current_lll_mode) {
        case LLL_MODE_OFF:
            current_lll_mode = LLL_MODE_LAYERS_ONLY;
            // Assuming that the mode switch keycode is mapped on a layer and the user is still holding the layer toggle key,
            // the keyboard will now show the colors for that layer.
            break;
        case LLL_MODE_LAYERS_ONLY:
            current_lll_mode = LLL_MODE_NIGHT;
            LLL_TEMPORARY_SHOW_BASE_LAYER_COLORS = true;
            break;
        case LLL_MODE_NIGHT:
            current_lll_mode = LLL_MODE_EXPLANTORY;
            LLL_TEMPORARY_SHOW_BASE_LAYER_COLORS = true;
            break;
        case LLL_MODE_EXPLANTORY:
            current_lll_mode = LLL_MODE_OFF;
            break;
    }
}


/*
    Most keys should get a color via their assigned key type.
    To keep this list short and avoid over-abstraction, we'll also have some keycodes directly assigned a color.

    Note that while Shift behaves like a layer, it isn't one.
    We could add an exceptional color rule for when Shift is pressed, but other than the numbers, no key changes type.
    So there's no use for that.
*/
enum KEY_COLOR_TYPE {
    // unmapped keys
    KEY_COLOR_UNMAPPED,

    // fallback for unclassified keys
    KEY_COLOR_UNCLASSIFIED,

    // Shift, Ctrl, Alt, GUI
    KEY_COLOR_MODIFIER,

    // AltGr and Fn and the magic accent-combining layer and the Windows layer
    // may the one-shot layer should have a different color... but we can do that via a direct keycode rule.
    KEY_COLOR_LAYER_TOGGLE,

    // arrows are special because their inverted T shape hints at what this color means
    KEY_COLOR_ARROW,

    // other nav keys
    KEY_COLOR_NAVIGATION,

    // F-keys.
    KEY_COLOR_FUNCTION,

    // Letters matters for accented letters, because plain letters are obvious on the base layer.
    // but it's nice that by seeing the color for plain letters on the base layer, we can guess what it means on the other layers.
    KEY_COLOR_LETTER,

    // useless for discovery, but a nice touch for the base layer.
    KEY_COLOR_NUMBER,

    // Maybe we should distinguish between prose punctuation and technical symbols?
    KEY_COLOR_PUNCTUATION,

    // Currency symbols and units like %. My feeling is that & and / still count as punctuation.
    // Maybe * and + and = could count as numeric operators. Although it's weird, since - and / are punctuation.
    KEY_COLOR_SYMBOL,
};

enum KEY_COLOR_TYPE get_type(uint16_t keycode) {
    if (keycode >= KC_A && keycode <= KC_Z) {
        return KEY_COLOR_LETTER;
    }
    if (keycode >= KC_1 && keycode <= KC_0) {
        return KEY_COLOR_NUMBER;
    }
    if (keycode >= KC_F1 && keycode <= KC_F12) {
        return KEY_COLOR_FUNCTION;
    }
    if (IS_QK_LAYER_TAP(keycode) || IS_QK_MOMENTARY(keycode) || IS_QK_ONE_SHOT_LAYER(keycode)) {
        return KEY_COLOR_LAYER_TOGGLE;
    }
    switch (keycode) {
        case KC_NO:
            return KEY_COLOR_UNMAPPED;

        case KC_LCTL:
        case KC_RCTL:
        case KC_LSFT:
        case KC_RSFT:
        case KC_LALT:
        case KC_RALT:
        case KC_LGUI:
        case KC_RGUI:
        // TODO
        // case OSM_ALT:
        // case OSM_CTL:
        // case OSM_SFT:
        // case OSM_GUI:
            return KEY_COLOR_MODIFIER;

        case KC_LEFT:
        case KC_RIGHT:
        case KC_UP:
        case KC_DOWN:
            return KEY_COLOR_ARROW;

        // TODO: custom nav keys with Ctrl
        case KC_HOME:
        case KC_END:
        case KC_PGUP:
        case KC_PGDN:
            return KEY_COLOR_NAVIGATION;

        case KC_COMMA:
        case KC_DOT:
        case KC_SCLN:
        case KC_QUOT:
        case KC_MINS:
        case KC_SLSH:
            return KEY_COLOR_PUNCTUATION;

        // TODO: add shifted characters that are mapped on AltGr layer
        // (No need to include those from shifted base layer,
        // since they are labelled on the keyboard and we don't change colors when Shift is pressed.)
        case KC_EQL:
        case KC_BSLS:
        case KC_PIPE:
        case KC_GRV:
        case KC_LBRC:
        case KC_RBRC:
        case KC_LPRN:
        case KC_RPRN:
        case US_SECT:
        case US_CENT:
        case US_PND:
        case US_EURO:
        // case UC_PMIL:  TODO: extract the definitions into a shared header file.
            return KEY_COLOR_SYMBOL;

        default:
            return KEY_COLOR_UNCLASSIFIED;
    }
}

#define HSV_DIM_WHITE           0, 0, 128


void set_color_for_keycode(uint8_t index, uint16_t keycode) {
    switch (get_type(keycode)) {
        case KEY_COLOR_UNMAPPED:
            // switch off the light
            rgb_matrix_set_hsv_color(index, HSV_BLACK);
            break;
        case KEY_COLOR_UNCLASSIFIED:
            rgb_matrix_set_hsv_color(index, HSV_DIM_WHITE);
            break;

        // four different character classes all in the warm color range.
        case KEY_COLOR_LETTER:
            rgb_matrix_set_hsv_color(index, HSV_WHITE);
            break;
        case KEY_COLOR_NUMBER:
            rgb_matrix_set_hsv_color(index, HSV_YELLOW);
            break;
        case KEY_COLOR_PUNCTUATION:
            rgb_matrix_set_hsv_color(index, HSV_ORANGE);
            break;
        case KEY_COLOR_SYMBOL:
            rgb_matrix_set_hsv_color(index, HSV_GOLDENROD);
            break;

        // two navigation classes
        case KEY_COLOR_ARROW:
            rgb_matrix_set_hsv_color(index, HSV_BLUE);
            break;
        case KEY_COLOR_NAVIGATION:
            rgb_matrix_set_hsv_color(index, HSV_GREEN);
            break;

        // mods and toggles
        case KEY_COLOR_MODIFIER:
            rgb_matrix_set_hsv_color(index, HSV_RED);
            break;
        case KEY_COLOR_LAYER_TOGGLE:
            rgb_matrix_set_hsv_color(index, HSV_PURPLE);
            break;

        // a class apart
        case KEY_COLOR_FUNCTION:
            rgb_matrix_set_hsv_color(index, HSV_PINK);
            break;
    }
}
