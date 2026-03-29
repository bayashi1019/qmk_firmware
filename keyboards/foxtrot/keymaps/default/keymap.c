#include <stdint.h>
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
static uint16_t pass_timer;
static uint16_t screenshot_timer;

enum custom_keycodes {
    PASS = SAFE_RANGE,
    WINR,
    SCR_ESC
};

/* =========================
 * キー処理
 * ========================= */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case PASS:
            if (record->event.pressed) {
                pass_timer = timer_read();
            } else {
                if (timer_elapsed(pass_timer) < 200) {
                    SEND_STRING("n0bu.s2603");
                } else {
                    register_code(KC_LCTL);
                    register_code(KC_LALT);
                    tap_code(KC_DEL);
                    unregister_code(KC_LALT);
                    unregister_code(KC_LCTL);

                    wait_ms(3000);
                    SEND_STRING("TKY");
                    tap_code16(JP_YEN);   // ← これが「\」
                    SEND_STRING("057126");
                    wait_ms(500);
                    tap_code(KC_TAB);
                    wait_ms(500);
                    SEND_STRING("n0bu.s2603");
                    wait_ms(500);
                    tap_code(KC_ENTER);
                }
            }
            return false;

        case WINR:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_R);
                unregister_code(KC_LGUI);

                wait_ms(500);

                register_code(KC_LCTL);
                tap_code(KC_V);
                unregister_code(KC_LCTL);

                tap_code(KC_ENTER);
            }
            return false;

        case SCR_ESC:
            if (record->event.pressed) {
                screenshot_timer = timer_read();
            } else {
                if (timer_elapsed(screenshot_timer) < 200) {
                    tap_code(KC_ESC);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }
            }
            return false;
    }
    return true;
}

/* =========================
 * キーマップ
 * ========================= */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_fullsize_iso(     
        SCR_ESC,  KC_LGUI,  WINR,     PASS,     KC_LEFT,  KC_UP,    KC_DOWN,  KC_RGHT,  KC_DEL,
        JP_ZKHK,  JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     JP_6,     JP_7,     JP_8,     JP_9,     JP_0,      JP_MINS,   JP_CIRC,   JP_YEN,    KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      JP_AT,     JP_LBRC,   KC_ENT,
        KC_LSFT,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     JP_SCLN,   JP_COLN,   JP_RBRC,
        KC_LCTL,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     JP_COMM,  JP_DOT,   JP_SLSH,   JP_BSLS,   KC_RSFT,
        MS_BTN1,  KC_SPC,   MS_BTN2
    )
};

