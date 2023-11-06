#include QMK_KEYBOARD_H
#include "keymap_user_config.h"

typedef union {
    uint32_t raw;
    struct {
        // Put configs here
        uint16_t locked_key :16; // first in order for better data alignment
        bool rgb_off :1;
        bool win_lock :1;
        bool lock_active :1;
        bool lock_searching :1;
    };
} user_config_t;

user_config_t user_config;

void eeconfig_init_user(void) {
    user_config.raw = 0;
    // Set default values for configs here (don't forget to add them in keymap_user_config.h)
    user_config.rgb_off = false;
    user_config.win_lock = false;
    user_config.lock_active = false;
    user_config.lock_active = false;
    user_config.locked_key = 0;
    eeconfig_update_user(user_config.raw);
}

void user_config_read(void) {
    user_config.raw = eeconfig_read_user();
}

void user_config_write(void) {
    eeconfig_update_user(user_config.raw);
}

// Put getters for configs here
bool user_config_get_rgb_off(void) { return user_config.rgb_off; }
bool user_config_get_win_lock(void) { return user_config.win_lock; }
bool user_config_get_lock_active(void) { return user_config.lock_active; }
bool user_config_get_lock_searching(void) { return user_config.lock_searching; }
uint16_t user_config_get_locked_key(void) { return user_config.locked_key; }

// Put setters (/togglers) for configs here (don't forget to add them in keymap_user_config.h)
void user_config_toggle_rgb_off(void) {
    user_config.rgb_off ^= 1;
    user_config_write();
}

void user_config_toggle_win_lock(void) {
    user_config.win_lock ^= 1;
    user_config_write();
}

void user_config_set_lock_active(bool val) {
    user_config.lock_active = val;
    user_config_write();
}

void user_config_set_lock_searching(bool val) {
    user_config.lock_searching = val;
    user_config_write();
}

void user_config_set_locked_key(uint16_t keycode) {
    user_config.locked_key = keycode;
    user_config_write();
}
