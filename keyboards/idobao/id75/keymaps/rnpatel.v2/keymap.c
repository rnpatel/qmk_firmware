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

// defines the layers used
enum layers
{
    QWERTY,
    GAME,
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
    TD_SLASH,
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
     * │T(FUNC)│       │       │ O(LSH)|CTL/SPC│O(LCMD)│O(LOPT)│  ADJ  │ ROPT  │ RCMD  │  SPC  │   \   │       │       │T(FUNC)│
     * └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [QWERTY] = LAYOUT_ortho_5x15( KC_ESC,    KC_1,     KC_2,     KC_3,           KC_4,            KC_5,           SCMD(KC_LALT),  KC_UP,       ALL_T(KC_APP),  KC_6,     KC_7,    KC_8,     KC_9,     KC_0,     KC_BSPC, \
                                  KC_GRV,    KC_Q,     KC_W,     KC_E,           KC_R,            KC_T,           KC_LEFT,        KC_DOWN,     KC_RGHT,        KC_Y,     KC_U,    KC_I,     KC_O,     KC_P,     KC_EQL,  \
                                  KC_LCTL,   KC_A,     KC_S,     KC_D,           KC_F,            KC_G,           KC_TAB,         XXXXXXX,     KC_ENT,         KC_H,     KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT, \
                                  KC_LSFT,   KC_Z,     KC_X,     KC_C,           KC_V,            KC_B,           TD(TD_LBRKT),   XXXXXXX,     TD(TD_RBRKT),   KC_N,     KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_MINS, \
                                  TT(FUNC),  XXXXXXX,  XXXXXXX,  OSM(MOD_LSFT),  LCTL_T(KC_SPC),  OSM(MOD_LGUI),  OSM(MOD_LALT),  MO(ADJUST),  KC_RALT,        KC_RGUI,  KC_SPC,  KC_BSLS,  XXXXXXX,  XXXXXXX,  TT(FUNC) ),

    /* GAME
     * ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     * │ Esc   │   1   │   2   │   3   │   4   │   5   │  MEH  │  Up   │ HYPER │   6   │   7   │   8   │   9   │   0   │ Bksp  │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │   `   │   Q   │   W   │   E   │   R   │   T   │ Left  │ Down  │ Right │   Y   │   U   │   I   │   O   │   P   │   =   │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │ Ctrl  │   A   │   S   │   D   │   F   │   G   │  TAB  │       │ ENTER │   H   │   J   │   K   │   L   │   ;   │   '   │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │ LShft │   Z   │   X   │   C   │   V   │   B   │   [   │       │   ]   │   N   │   M   │   ,   │   .   │   /   │   -   │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │M(FUNC)│       │       │ LShft | Space │ LCMD  │ LOPT  |       │ ROPT  │ RCMD  │  SPC  │   \   │       │       │QWERTY │
     * └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [GAME] = LAYOUT_ortho_5x15( KC_ESC,    KC_1,     KC_2,     KC_3,     KC_4,    KC_5,     SCMD(KC_LALT),  KC_UP,    ALL_T(KC_APP),  KC_6,     KC_7,    KC_8,     KC_9,     KC_0,     KC_BSPC,   \
                                KC_GRV,    KC_Q,     KC_W,     KC_E,     KC_R,    KC_T,     KC_LEFT,        KC_DOWN,  KC_RGHT,        KC_Y,     KC_U,    KC_I,     KC_O,     KC_P,     KC_EQL,    \
                                KC_LCTL,   KC_A,     KC_S,     KC_D,     KC_F,    KC_G,     KC_TAB,         XXXXXXX,  KC_ENT,         KC_H,     KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   \
                                KC_LSFT,   KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,     KC_LBRC,        XXXXXXX,  KC_RBRC,        KC_N,     KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_MINS,   \
                                MO(FUNC),  XXXXXXX,  XXXXXXX,  KC_LSFT,  KC_SPC,  KC_LGUI,  KC_LALT,        XXXXXXX,  KC_RALT,        KC_RGUI,  KC_SPC,  KC_BSLS,  XXXXXXX,  XXXXXXX,  TO(QWERTY) ),

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
     * │ RGBUP │ HUEUP │ SATUP │ VALUP │ SPDUP │       │       │       │       │ PLAIN │BREATHE│SCROLL │ SWIRL │       │       │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │ RGBDN │ HUEDN │ SATDN │ VALDN │ SPDND │       │       │       │       │       │       │       │       │       │       │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │RGB_TOG│       │       │       │       │       │       │       │       │       │       │       │       │       │       │
     * ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     * │       │       │       │       │       │       │       │  ADJ  │       │       │       │       │       │       │  GAME │
     * └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [ADJUST] = LAYOUT_ortho_5x15( XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
                                  RGB_MOD,   RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_M_SW, XXXXXXX,  XXXXXXX, \
                                  RGB_RMOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
                                  RGB_TOG,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
                                  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(GAME) ),
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

typedef struct {
    int col;
    int row;
} VEC2;

// #define HIGHLIGHT_COLOR     0xFF, 0x00, 0x00
// #define ONESHOT_COLOR       0x00, 0xFF, 0x00
// #define STICKY_COLOR        0x00, 0x00, 0xFF

#define HIGHLIGHT_COLOR     RGB_WHITE
#define ONESHOT_COLOR       RGB_ORANGE
#define STICKY_COLOR        RGB_PURPLE

void matrix_scan_user(void)
{
    uint8_t sticky = get_oneshot_locked_mods();
    uint8_t oneshots = get_oneshot_mods();
    uint8_t mods = get_mods();

    uint8_t allMods = sticky | oneshots | mods;

    VEC2 sft[] = { {0, 3}, {3, 4} };
    VEC2 ctr[] = { {0, 2}, {4, 4} };
    VEC2 opt[] = { {6, 4}, {8, 4} };
    VEC2 cmd[] = { {5, 4}, {9, 4} };

    if (!oneshots && !mods) return;

    if (allMods & MOD_MASK_CTRL)
    {
        uint8_t s = sticky & MOD_MASK_CTRL;
        uint8_t o = oneshots & MOD_MASK_CTRL;

        for (int i = 0; i < 2; i++)
        {
            VEC2 vec = ctr[i];
            int index = g_led_config.matrix_co[vec.row][vec.col];
            if (s)      rgb_matrix_set_color(index, STICKY_COLOR);
            else if (o) rgb_matrix_set_color(index, ONESHOT_COLOR);
            else        rgb_matrix_set_color(index, HIGHLIGHT_COLOR);
        }
    }

    if (allMods & MOD_MASK_ALT)
    {
        uint8_t s = sticky & MOD_MASK_ALT;
        uint8_t o = oneshots & MOD_MASK_ALT;

        for (int i = 0; i < 2; i++)
        {
            VEC2 vec = opt[i];
            int index = g_led_config.matrix_co[vec.row][vec.col];
            if (s)      rgb_matrix_set_color(index, STICKY_COLOR);
            else if (o) rgb_matrix_set_color(index, ONESHOT_COLOR);
            else        rgb_matrix_set_color(index, HIGHLIGHT_COLOR);
        }
    }

    if (allMods & MOD_MASK_GUI)
    {
        uint8_t s = sticky & MOD_MASK_GUI;
        uint8_t o = oneshots & MOD_MASK_GUI;

        for (int i = 0; i < 2; i++)
        {
            VEC2 vec = cmd[i];
            int index = g_led_config.matrix_co[vec.row][vec.col];
            if (s)      rgb_matrix_set_color(index, STICKY_COLOR);
            else if (o) rgb_matrix_set_color(index, ONESHOT_COLOR);
            else        rgb_matrix_set_color(index, HIGHLIGHT_COLOR);
        }
    }

    if (allMods & MOD_MASK_SHIFT)
    {
        uint8_t s = sticky & MOD_MASK_SHIFT;
        uint8_t o = oneshots & MOD_MASK_SHIFT;

        for (int i = 0; i < 2; i++)
        {
            VEC2 vec = sft[i];
            int index = g_led_config.matrix_co[vec.row][vec.col];
            if (s)      rgb_matrix_set_color(index, STICKY_COLOR);
            else if (o) rgb_matrix_set_color(index, ONESHOT_COLOR);
            else        rgb_matrix_set_color(index, HIGHLIGHT_COLOR);
        }
    }
}

void led_set_user(uint8_t usb_led)
{

}

void rnp_set_alpha_key_color(uint8_t red, uint8_t green, uint8_t blue)
{
    int row = 0;
    int col = 0;
    int index;

    for (row = 1; row <= 3; row++)
    {
        for (col = 1; col <= 5; col++)
        {
            index = g_led_config.matrix_co[row][col];
            rgb_matrix_set_color(index, red, green, blue);
        }

        for (col = 9; col <= 13; col++)
        {
            index = g_led_config.matrix_co[row][col];
            rgb_matrix_set_color(index, red, green, blue);
        }
    }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
    switch(get_highest_layer(layer_state | default_layer_state))
    {
        case FUNC:
        {
            rnp_set_alpha_key_color(RGB_ORANGE);
            break;
        }
        case GAME:
        {
            rnp_set_alpha_key_color(RGB_GREEN);
            break;
        }
        case ADJUST:
        {
            rnp_set_alpha_key_color(RGB_PURPLE);
            break;
        }
        default:
        {
            break;
        }
    }
}
/*
  void set_rgblight_by_layer(uint32_t layer) {
    for (int i = 0; i < led_count; i++) {
        switch (layer) {
            case _LOCK:
            case _ROMAK:
                break;
            case _NUMPAD:
                rgb_matrix_set_color(leds[i], RGB_PURPLE);
                break;
            case _MAINTENANCE:
                rgb_matrix_set_color(leds[i], RGB_RED);
                break;
            default:
                rgb_matrix_set_color(leds[i], RGB_SPRINGGREEN);
                break;
        }
    }
}

void set_current_layer_rgb(void) {
    set_rgblight_by_layer(get_highest_layer(layer_state | default_layer_state));
}

layer_state_t layer_state_set_user(layer_state_t state) {
    set_rgblight_by_layer(biton32(state));
    return state;
}

void rgb_matrix_indicators_user(void) {
    uint8_t mods                = get_mods();
    uint8_t oneshot_mods        = get_oneshot_mods();
    uint8_t oneshot_locked_mods = get_oneshot_locked_mods();

    bool isShift = mods & MOD_MASK_SHIFT || oneshot_mods & MOD_MASK_SHIFT || oneshot_locked_mods & MOD_MASK_SHIFT;
    bool isCtrl  = mods & MOD_MASK_CTRL || oneshot_mods & MOD_MASK_CTRL || oneshot_locked_mods & MOD_MASK_CTRL;
    bool isAlt   = mods & MOD_MASK_ALT || oneshot_mods & MOD_MASK_ALT || oneshot_locked_mods & MOD_MASK_ALT;
    bool isGui   = mods & MOD_MASK_GUI || oneshot_mods & MOD_MASK_GUI || oneshot_locked_mods & MOD_MASK_GUI;

    for (int i = 0; i < led_count; i++) {
        if (swapper.state != NONE || leader.isLeading || select_word.state != STATE_NONE) {
            rgb_matrix_set_color(leds[i], RGB_GREEN);
        } else if (has_any_smart_case()) {
            rgb_matrix_set_color(leds[i], RGB_YELLOW);
        } else if (isShift) {
            rgb_matrix_set_color(leds[i], RGB_TEAL);
        } else if (isCtrl || isAlt || isGui) {
            rgb_matrix_set_color(leds[i], RGB_WHITE);
        } else {
            set_current_layer_rgb();
        }
    }
}
*/
