#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "rgb_matrix_user.h"
#include "keymap_user.h"
#include "keymap_user_config.h"

extern uint8_t factory_reset_count;
extern enum {
    LED_TEST_MODE_OFF,
    LED_TEST_MODE_WHITE,
    LED_TEST_MODE_RED,
    LED_TEST_MODE_GREEN,
    LED_TEST_MODE_BLUE,
    LED_TEST_MODE_MAX
} led_test_mode;

keypos_t led_index_key_position[RGB_MATRIX_LED_COUNT];
bool is_suspended = false;

void suspend_power_down_user(void) {
    // code will run multiple times while keyboard is suspended
    is_suspended = true;
}

void suspend_wakeup_init_user(void) {
    // code will run on keyboard wakeup
    is_suspended = false;
}

void rgb_matrix_init_user(void) {
    for(uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for(uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if(led_index != NO_LED) {
                led_index_key_position[led_index] = (keypos_t){.row = row, .col = col};
            }
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // if(!rgb_matrix_indicators_advanced_keychron(led_min, led_max)) { return false; }

    if(led_test_mode || factory_reset_count) { return false; }

    if(is_suspended || user_config_get_rgb_off()) { // is_suspended doesn't work/have any effect (or at least not the expected one)
        rgb_matrix_set_base_colors(led_min, led_max, RGB_OFF);
        return false;
    }

    uint8_t current_layer = get_highest_layer(layer_state|default_layer_state);
    switch(current_layer) {
        case BASE:
        case BASE2:
            // rgb_matrix_set_remapped_colors();
#ifdef RGB_ACCENT_COLOR
            if(host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_caps_lock_indicator, RGB_ACCENT_COLOR);
            }
            // Deprecated since scroll lock is remapped to KC_LOCK
            /* if(host_keyboard_led_state().scroll_lock) {
                rgb_matrix_set_color(14, RGB_ACCENT_COLOR); // 14 = Scroll Lock
            } */
            if(user_config_get_win_lock()) {
                rgb_matrix_set_color(78, RGB_ACCENT_COLOR); // 78 = Left Windows
            }
#endif
            if(user_config_get_lock_active() && user_config_get_lock_searching()) { // wants to lock a key
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_kc_lock_key, RGB_GREEN);
            } else if(user_config_get_lock_active()) { // locked a key
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_kc_lock_key, RGB_RED);
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_locked_key, RGB_RED);
            }
            break;
        case FN:
        case FN2:
#ifdef RGB_ACCENT_COLOR
            rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_not_transparent, RGB_ACCENT_COLOR);
#endif
            break;
    }
    return false;
}

void rgb_matrix_set_base_colors(uint8_t led_min, uint8_t led_max, uint8_t red, uint8_t green, uint8_t blue) {
    for(uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, red, green, blue);
    }
}

/* void rgb_matrix_set_remapped_colors(void) {
    // remapped keys: WASD, IJKL, arrow keys
    uint8_t remappedkeys[] = {35, 41, 50, 51, 52, 56, 57, 58, 76, 85, 86, 87};
    for(uint8_t i = 0; i < sizeof(remappedkeys)/sizeof(remappedkeys[0]); i++) {
        rgb_matrix_set_color(remappedkeys[i], RGB_WHITE);
    }
} */

void rgb_matrix_set_color_by_keycode(uint8_t led_min, uint8_t led_max, uint8_t layer, bool (*is_keycode)(uint16_t), uint8_t red, uint8_t green, uint8_t blue) {
    for(uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(layer, led_index_key_position[i]);
        if((*is_keycode)(keycode)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
    }
}

bool is_caps_lock_indicator(uint16_t keycode) {
    return (KC_A <= keycode && keycode <= KC_0) || (KC_MINS < keycode && keycode <= KC_CAPS && keycode != KC_EQL && keycode != KC_GRV);
}

// bool is_transparent(uint16_t keycode) { return keycode == KC_TRNS; }
bool is_not_transparent(uint16_t keycode) { return keycode != KC_TRNS; }
bool is_kc_lock_key(uint16_t keycode) { return keycode == KC_LOCK; }
bool is_locked_key(uint16_t keycode) { return keycode == user_config_get_locked_key(); }
