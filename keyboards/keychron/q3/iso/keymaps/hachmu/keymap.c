#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "keymap_user.h"
#include "keymap_user_config.h"
#include "rgb_matrix_user.h"

bool bootloader_pressed = false;
bool do_bootloader = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_tkl_iso(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,              KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,    KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(FN),   KC_NO,      KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RIGHT),

    [FN] = LAYOUT_tkl_iso(
        _______,            _______,  _______,  _______,  _______,  KC_BRID,  KC_BRIU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  KC_LOCK,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  KC_WH_U,
        RGB_TOG,  _______,  RGB_VAI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  KC_WH_D,
        _______,  _______,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    KC_BTN1,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              KC_BTN2,            KC_MS_UP,
        _______,  GU_TOGG,  _______,                                _______,                                _______,  _______,  _______,    KC_BTN3, KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT),

    [BASE_2] = LAYOUT_tkl_iso(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,              KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,    KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(FN_2), KC_NO,      KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RIGHT),

    [FN_2] = LAYOUT_tkl_iso(
        _______,            _______,  _______,  _______,  _______,  KC_BRID,  KC_BRIU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  KC_LOCK,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  KC_WH_U,
        RGB_TOG,  _______,  RGB_VAI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  KC_WH_D,
        _______,  _______,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    KC_BTN1,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              KC_BTN2,            KC_MS_UP,
        _______,  GU_TOGG,  _______,                                _______,                                _______,  _______,  _______,    KC_BTN3, KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT),
};

void housekeeping_task_user(void) {
    if(do_bootloader) {
        // bootloader was pressed on previous frame, RGB should now be off,
        // so we can now call the bootloader
        reset_keyboard();
    } else if(bootloader_pressed) {
        // User pressed bootloader combo and RGB was disabled earlier in this
        // frame. We set a flag here to call the bootloader at end of
        // the next frame.
        do_bootloader = true;
    }
    housekeeping_task_keychron();
}

void matrix_init_user(void) {
    rgb_matrix_init_user();
}

void keyboard_post_init_user(void) {
    user_config_read();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(182, 255, 255);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(process_record_keychron(keycode, record)) {
        switch(keycode) {
            case QK_BOOT:
                // We want to turn off LEDs before calling bootloader, so here
                // we call rgb_matrix_disable_noeeprom() and set a flag because
                // the LEDs won't be updated until the next frame.
                rgb_matrix_disable_noeeprom();
                bootloader_pressed = true;
                return false; // Skip any further processing of this key
            case KC_LOCK:
                if(record->event.pressed == 1) { // Do nothing special on key down
                    return true;
                } else { // On key up, toggle on/off
                    if(user_config_get_lock_active()) { // If lock is active then turn off
                        endLock(user_config_get_locked_key());
                        return false;
                    } else { // If lock off, turn on
                        beginLock();
                        return false;
                    }
                }
                break;
            case RGB_TOG:
                if(record->event.pressed == 0) { // On key-release
                    user_config_toggle_rgb_off();
                }
                return true;
            case GU_TOGG:
                if(record->event.pressed == 1) { // On key-release
                    user_config_toggle_win_lock();
                }
                return true;
            default:
                if(user_config_get_lock_active()) { // Lock is active, need to execute steps that don't involve lock key
                    if(user_config_get_lock_searching() && keycode < 0xFF && record->event.pressed == 0 ) { // Lock key pressed, which turned on search.  Key needs to be valid.  On key up, set as locked key
                        lockKey(keycode);
                        return false;
                    } else if(!user_config_get_lock_searching() && keycode == user_config_get_locked_key()) { // If the key has already been set, ignore the button press
                       return false;
                    }
                }
                // If searching is false or its a quantum key, then continue on.
                // If the locked key has already been set, a normal button push will add to the effect
                return true; // Process all other keycodes normally (Non-lock related keypresses)
        }
    }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    /* if(!dip_switch_update_keychron(index, active)) {
        return false;
    } */
    return true;
}

// Lock Key Functionality

void beginLock(void) {
  user_config_set_lock_active(true);
  user_config_set_lock_searching(true);
}

void lockKey(uint16_t keycode) {
  user_config_set_locked_key(keycode);
  register_code(keycode);
  user_config_set_lock_searching(false);
}

void endLock(uint16_t keycode) {
  user_config_set_lock_active(false);
  unregister_code(keycode);
  user_config_set_locked_key(0);
}
