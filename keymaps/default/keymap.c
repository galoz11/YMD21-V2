/* Copyright 2021 Guy
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3,
    _FN4
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
 		RESET, KC_F2, KC_F3, KC_F4, 
		KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, 
		KC_P7, KC_P8, KC_P9, KC_PEQL, 
		KC_P4, KC_P5, KC_P6, KC_PPLS, 
		KC_P1, KC_P2, KC_P3, KC_SPC, 
		TG(1), KC_P0, KC_PDOT, KC_PENT
    ),
    [_FN1] = LAYOUT(
		RGB_MOD, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_TWINKLE, 
		BL_TOGG, RGB_TOG, RGB_VAD, RGB_VAI, 
		BL_STEP, KC_TRNS, RGB_HUI, RGB_HUD, 
		KC_TRNS, KC_TRNS, RGB_SAI, RGB_SAD, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		TG(1), KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN2] = LAYOUT(
		RGB_MOD, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_TWINKLE, 
		BL_TOGG, RGB_TOG, RGB_VAD, RGB_VAI, 
		BL_STEP, KC_TRNS, RGB_HUI, RGB_HUD, 
		KC_TRNS, KC_TRNS, RGB_SAI, RGB_SAD, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		TG(1), KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN3] = LAYOUT(
		RGB_MOD, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_TWINKLE, 
		BL_TOGG, RGB_TOG, RGB_VAD, RGB_VAI, 
		BL_STEP, KC_TRNS, RGB_HUI, RGB_HUD, 
		KC_TRNS, KC_TRNS, RGB_SAI, RGB_SAD, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		TG(1), KC_TRNS, KC_TRNS, KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
};
//Guy MANIPULATION
// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 4, HSV_RED}       // Light 4 LEDs, starting with LED 6
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 4, HSV_CYAN}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 4, HSV_PURPLE}
);
// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 4, HSV_GREEN}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
};


bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, _FN1));
    rgblight_set_layer_state(3, layer_state_cmp(state, _FN2));
    return state;
}