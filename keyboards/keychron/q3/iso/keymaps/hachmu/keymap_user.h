#pragma once

enum layers {
    BASE,
    FN,
    BASE2,
    FN2
};

enum my_keycodes {
    KC_LOCK = SAFE_RANGE
};

#define KC_LCK KC_LOCK

void beginLock(void);
void lockKey(uint16_t keycode);
void endLock(uint16_t keycode);
