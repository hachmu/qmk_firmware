#pragma once

void rgb_matrix_init_user(void);
void rgb_matrix_set_base_colors(uint8_t led_min, uint8_t led_max, uint8_t red, uint8_t green, uint8_t blue);
// void rgb_matrix_set_remapped_colors(void);
void rgb_matrix_set_color_by_keycode(uint8_t led_min, uint8_t led_max, uint8_t layer, bool (*is_keycode)(uint16_t), uint8_t red, uint8_t green, uint8_t blue);

bool is_caps_lock_indicator(uint16_t keycode);
// bool is_transparent(uint16_t keycode);
bool is_not_transparent(uint16_t keycode);
bool is_kc_lock_key(uint16_t keycode);
bool is_locked_key(uint16_t keycode);
