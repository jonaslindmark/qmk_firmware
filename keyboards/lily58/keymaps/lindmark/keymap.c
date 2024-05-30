#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ROTARY,
};

uint8_t rotary_mode = 0;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | =    |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Tab |  Q   |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LCTL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| RAISE |    | rota  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | ~L1  |  ESC | /Space  /       \Enter \  |`/RCTL| BSPC | RALT |
 *                   |      |      |RGUI  |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_EQL,         KC_1, KC_2, KC_3,    KC_4,  KC_5,                           KC_6,             KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
  KC_TAB,         KC_Q, KC_W, KC_E,    KC_R,  KC_T,                           KC_Y,             KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  KC_LCTL,        KC_A, KC_S, KC_D,    KC_F,  KC_G,                           KC_H,             KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,        KC_Z, KC_X, KC_C,    KC_V,  KC_B,          RAISE,  ROTARY,  KC_N,             KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                              KC_LALT, LOWER, LGUI_T(KC_ESC),KC_SPC, KC_ENT,  RCTL_T(KC_GRAVE), KC_BSPC, KC_RALT \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  | F9   | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | Mute | VUp  | VDn  |      |                    |      |  [   |  ]   |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | MStop|MPre  |MNxt  |MPlay |-------.    ,-------|  LEFT | DOWN |  UP | RIGHT|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | ScrU | ScrDo|      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \ DEL  \  | BSPC |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,       KC_F8,         KC_F9,   KC_F10,  KC_F11, \
  _______, _______, KC_MUTE, KC_VOLU, KC_VOLD, _______,                   _______, KC_LBRC,     KC_RBRC,       _______, _______, _______,\
  _______, _______, KC_MSTP, KC_MPRV, KC_MNXT, KC_MPLY,                   KC_LEFT, KC_DOWN,     KC_UP,         KC_RIGHT,_______,_______,\
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_WH_DOWN,KC_MS_WH_UP,  _______, _______, _______, \
                             _______, _______, _______, _______, KC_DEL, KC_BSPC,  _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| MouL | MouD | MouU |  MouR|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                       _______,    _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                       _______,    _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                       KC_MS_L,    KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,     _______,    _______, _______, _______, _______, _______, \
                            _______, _______, _______,  KC_DEL,  KC_MS_BTN1,  KC_MS_BTN2, _______, _______ \
)
};

void matrix_init_user(void) {
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
  } else {
    oled_write(read_logo(), false);
  }
  return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case ROTARY:
        if (record->event.pressed) {
          rotary_mode = (rotary_mode + 1) % 2;
        }
        return false;
        break;
  }
  return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
      return false; /* Don't process further events if user function exists and returns false */
    }
    if (rotary_mode == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) {
        if (clockwise) {
          tap_code(KC_AUDIO_VOL_DOWN);
        } else {
          tap_code(KC_AUDIO_VOL_UP);
        }
    }
    return true;
}
#endif
