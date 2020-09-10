/* Copyright 2018 MechMerlin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define ONESHOT_TAP_TOGGLE 1  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 3000  /* Time (in ms) before the one shot key is released */

// defines the layers used
enum layers
{
    QWERTY,
    FUNC,
    ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes
{
  QMKBEST = SAFE_RANGE,
  QMKURL
};

// defines the tapdance keycodes
enum tap_dance_keycodes
{
    TD_LBRKT,
    TD_RBRKT,
};

void tapdance_lbrkt(qk_tap_dance_state_t *state, void *user_data);
void tapdance_rbrkt(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] =
{
    [TD_LBRKT] = ACTION_TAP_DANCE_FN(tapdance_lbrkt),
    [TD_RBRKT] = ACTION_TAP_DANCE_FN(tapdance_rbrkt),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
    /* QWERTY
     * ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     * │ Esc   │   1   │   2   │   3   │   4   │   5   │  MEH  │  Up   │ HYPER │   6   │   7   │   8   │   9   │   0   │ Bksp  │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │   `   │   Q   │   W   │   E   │   R   │   T   │ Left  │ Down  │ Right │   Y   │   U   │   I   │   O   │   P   │   =   │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │ Ctrl  │   A   │   S   │   D   │   F   │   G   │  TAB  │       │ ENTER │   H   │   J   │   K   │   L   │   ;   │   '   │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │ LShft │   Z   │   X   │   C   │   V   │   B   │  ([{  │       │  }])  │   N   │   M   │   ,   │   .   │   /   │   -   │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │T(FUNC)│       │       │ LShft |CTL/SPC│O(LCMD)│O(LOPT)│  ADJ  │ ROPT  │ RCMD  │  SPC  │   \   │       │       │T(FUNC)│
     * └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [QWERTY] = LAYOUT_ortho_5x15( KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,            KC_5,           SCMD(KC_LALT),  KC_UP,      ALL_T(KC_APP),  KC_6,     KC_7,    KC_8,     KC_9,     KC_0,     KC_BSPC, \
                                  KC_GRV,   KC_Q,     KC_W,     KC_E,     KC_R,            KC_T,           KC_LEFT,        KC_DOWN,    KC_RGHT,        KC_Y,     KC_U,    KC_I,     KC_O,     KC_P,     KC_EQL,  \
                                  KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,            KC_G,           KC_TAB,         XXXXXXX,    KC_ENT,         KC_H,     KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT, \
                                  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,            KC_B,           TD(TD_LBRKT),   XXXXXXX,    TD(TD_RBRKT),   KC_N,     KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_MINS, \
                                  TT(FUNC), XXXXXXX,  XXXXXXX,  KC_LSFT,  LCTL_T(KC_SPC),  OSM(MOD_LGUI),  OSM(MOD_LALT),  MO(ADJUST), KC_RALT,        KC_RGUI,  KC_SPC,  KC_BSLS,  XXXXXXX,  XXXXXXX,  TT(FUNC) ),

    /* FUNC
     * ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     * │  Esc  │  F1   │  F2   │  F3   │  F4   │  F5   │  MEH  │       │ HYPER │  F6   │  F7   │  F8   │  F9   │  F10  │ Bksp  │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │       │       │       │ S(UP) │       │       │       │       │ Mute  │       │       │  Up   │       │       │  F11  │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │ PGUP  │ HOME  │S(LEFT)│S(DOWN)│S(RGHT)│       │       │       │ VolUp │       │ Left  │ Down  │ Right │       │  F12  │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │ PGDN  │  END  │       │       │       │       │       │       │ VolDn │       │ Prev  │ Pause │ Next  │       │       │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │T(FUNC)│       │       │ LShft |CTL/SPC│O(LCMD)│O(LOPT)│  ADJ  │ ROPT  │ RCMD  │  SPC  │   \   │       │       │T(FUNC)│
     * └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [FUNC] = LAYOUT_ortho_5x15( _______,  KC_F1,    KC_F2,          KC_F3,          KC_F4,          KC_F5,    _______,  XXXXXXX,  _______,      KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______, \
                                XXXXXXX,  XXXXXXX,  XXXXXXX,        RSFT(KC_UP),    XXXXXXX,        XXXXXXX,  XXXXXXX,  XXXXXXX,  KC__MUTE,     XXXXXXX,  XXXXXXX,  KC_UP,    XXXXXXX,  XXXXXXX,  KC_F11,  \
                                KC_PGUP,  KC_HOME,  RSFT(KC_LEFT),  RSFT(KC_DOWN),  RSFT(KC_RGHT),  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC__VOLUP,    XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_RGHT,  XXXXXXX,  KC_F12,  \
                                KC_PGDN,  KC_END,   XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,  XXXXXXX,  XXXXXXX,  KC__VOLDOWN,  XXXXXXX,  KC_MRWD,  KC_MPLY,  KC_MFFD,  XXXXXXX,  XXXXXXX, \
                                _______,  _______,  _______,        _______,        _______,        _______,  _______,  _______,  _______,      _______,  _______,  _______,  _______,  _______,  _______  ),

    /* ADJUST
     * ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     * │       │       │       │       │       │       │       │ RESET │       │       │       │       │       │       │       │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │ RGBUP │ HUEUP │ SATUP │ VALUP │ SPDUP │       │       │       │       │       │       │       │       │       │       │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │ RGBDN │ HUEDN │ SATDN │ VALDN │ SPDND │       │       │       │       │       │       │       │       │       │       │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │RGB_TOG│       │       │       │       │       │       │       │       │       │       │       │       │       │       │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │       │       │       │       │       │       │       │  ADJ  │       │       │       │       │       │       │       │
     * └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [ADJUST] = LAYOUT_ortho_5x15( XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
                                  RGB_MOD,   RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
                                  RGB_RMOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
                                  RGB_TOG,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
                                  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX  ),
};

void tapdance_lbrkt(qk_tap_dance_state_t *state, void *user_data)
{
    switch (state->count)
    {
        case 2:
            tap_code(KC_LBRC);
            break;
        case 3:
            register_code(KC_RSFT);
            tap_code(KC_LBRC);
            unregister_code(KC_RSFT);
            break;
        default:
            register_code(KC_RSFT);
            tap_code(KC_9);
            unregister_code(KC_RSFT);
            break;
    }
}

void tapdance_rbrkt(qk_tap_dance_state_t *state, void *user_data)
{
    switch (state->count)
    {
        case 2:
            tap_code(KC_RBRC);
            break;
        case 3:
            register_code(KC_RSFT);
            tap_code(KC_RBRC);
            unregister_code(KC_RSFT);
            break;
        default:
            register_code(KC_RSFT);
            tap_code(KC_0);
            unregister_code(KC_RSFT);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
        case QMKBEST:
        {
            if (record->event.pressed)
            {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            }
            else
            {
                // when keycode QMKBEST is released
            }
            break;
        }
        case QMKURL:
        {
            if (record->event.pressed)
            {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
            }
            else
            {
                // when keycode QMKURL is released
            }
            break;
        }
    }

    return true;
}

void matrix_init_user(void)
{

}

void matrix_scan_user(void)
{

}

void led_set_user(uint8_t usb_led)
{

}
