// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <iomanip>
#include <initializer_list>
#include <sstream>
#include <string>

#include "test_common.hpp"

extern "C" {
#include "quantum/rgb_matrix/animations/keycode_types.h"
#include "quantum/keycode_string.h"
}

class KeycodeTypesTest : public ::testing::Test {};

namespace {

std::string format_keycode(uint16_t keycode) {
    std::ostringstream oss;
    oss << get_keycode_string(keycode) << " (0x" << std::uppercase << std::hex << keycode << ")";
    return oss.str();
}

} // namespace

TEST_F(KeycodeTypesTest, GetTypeReturnsEveryColorType) {
    struct TypeCase {
        KEY_COLOR_TYPE                   type;
        std::initializer_list<uint16_t> keycodes;
    };

    const TypeCase cases[] = {
        {KEY_COLOR_LETTER, {KC_A, KC_Z, S(KC_A), ALGR(KC_Z)}},
        {KEY_COLOR_NUMBER, {KC_1, KC_0}},
        {KEY_COLOR_PUNCTUATION, {KC_COMMA, KC_SLASH}},
        {KEY_COLOR_SYMBOL, {KC_EQUAL, KC_LEFT_BRACKET}},
        {KEY_COLOR_MODIFIED_CHARACTER, {S(KC_COMMA), RSFT(KC_1), ALGR(KC_EQUAL), S(ALGR(KC_DOT))}},
        // {KEY_COLOR_COMBINING_ACCENT, {}},
        // {KEY_COLOR_OTHER_CHARACTER, {}},
        {KEY_COLOR_MODIFIER, {KC_LCTL, KC_RGUI}},
        {KEY_COLOR_ARROW, {KC_LEFT, KC_UP}},
        {KEY_COLOR_NAVIGATION, {KC_HOME, KC_PGDN}},
        {KEY_COLOR_FUNCTION, {KC_F1, KC_F12}},
        {KEY_COLOR_MEDIA_CONTROL, {KC_AUDIO_VOL_UP, KC_MEDIA_PLAY_PAUSE}},
        {KEY_COLOR_MODIFIED_KEY, {LCTL(KC_A), LGUI(KC_B), LALT(KC_C), S(KC_PGDN), ALGR(KC_F1)}},
        {KEY_COLOR_USB_OTHER, {KC_INSERT, KC_APPLICATION}},
        {KEY_COLOR_LAYER_TOGGLE, {MO(1), TG(2), TO(3), LT(4, KC_D), OSL(5)}},
        {KEY_COLOR_RGB_CONTROL, {QK_RGB_MATRIX_TOGGLE, QK_RGB_MATRIX_MODE_NEXT}},
        {KEY_COLOR_QMK_CONTROL, {QK_BOOT}},
        {KEY_COLOR_QMK_OTHER, {QK_USER_0, QK_MACRO_1}},
        {KEY_COLOR_UNMAPPED, {KC_NO, KC_TRANSPARENT}},
    };

    for (const auto& test_case : cases) {
        for (uint16_t keycode : test_case.keycodes) {
            SCOPED_TRACE(::testing::Message() << "keycode " << format_keycode(keycode));
            EXPECT_EQ(test_case.type, get_type(keycode));
        }
    }
}

class KeycodeModifierMacroTest : public ::testing::Test {};

TEST_F(KeycodeModifierMacroTest, RightAltMacroDetectsRightAlt) {
    EXPECT_TRUE(HAS_RIGHT_ALT_MOD(RALT(KC_A)));
}

TEST_F(KeycodeModifierMacroTest, RightAltMacroRejectsLeftAlt) {
    EXPECT_FALSE(HAS_RIGHT_ALT_MOD(LALT(KC_A)));
}

TEST_F(KeycodeModifierMacroTest, ShiftMacroDetectsEitherShift) {
    EXPECT_TRUE(HAS_SHIFT_MOD(RSFT(KC_B)));
    EXPECT_TRUE(HAS_SHIFT_MOD(LSFT(KC_C)));
}

TEST_F(KeycodeModifierMacroTest, ShiftMacroRejectsKeysWithoutShift) {
    EXPECT_FALSE(HAS_SHIFT_MOD(KC_D));
    EXPECT_FALSE(HAS_SHIFT_MOD(LCTL(KC_D)));
}

TEST_F(KeycodeModifierMacroTest, CtrlOrGuiMacroDetectsCtrl) {
    EXPECT_TRUE(HAS_CTRL_OR_GUI_MOD(LCTL(KC_E)));
}

TEST_F(KeycodeModifierMacroTest, CtrlOrGuiMacroDetectsGui) {
    EXPECT_TRUE(HAS_CTRL_OR_GUI_MOD(RGUI(KC_F)));
}

TEST_F(KeycodeModifierMacroTest, CtrlOrGuiMacroRejectsPlainKeys) {
    EXPECT_FALSE(HAS_CTRL_OR_GUI_MOD(KC_G));
}

TEST_F(KeycodeModifierMacroTest, AltMacroDetectsLeftAlt) {
    EXPECT_TRUE(HAS_ALT_MOD(LALT(KC_H)));
}

TEST_F(KeycodeModifierMacroTest, AltMacroDetectsRightAlt) {
    EXPECT_TRUE(HAS_ALT_MOD(RALT(KC_H)));
}

TEST_F(KeycodeModifierMacroTest, AltMacroRejectsNonAlt) {
    EXPECT_FALSE(HAS_ALT_MOD(KC_I));
}
