#pragma once

void user_config_read(void);
void user_config_write(void);
// Put getters for configs here
bool user_config_get_rgb_off(void);
bool user_config_get_win_lock(void);
bool user_config_get_lock_active(void);
bool user_config_get_lock_searching(void);
uint16_t user_config_get_locked_key(void);
// Put setters (/togglers) for configs here
void user_config_toggle_rgb_off(void);
void user_config_toggle_win_lock(void);
void user_config_set_lock_active(bool val);
void user_config_set_lock_searching(bool val);
void user_config_set_locked_key(uint16_t keycode);
