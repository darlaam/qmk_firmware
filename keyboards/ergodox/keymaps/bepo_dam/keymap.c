/* Bépo keymap  */
#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "keymap_extras/keymap_bepo.h"
#include "led.h"

enum layers {
    LR_BASE, // default bépo layer
    LR_MIRROR, // mirror layer (left hand mode)
    LR_NUMFN, // SYMB and mumeric keyboard
    LR_MEDIA, // media layer
};

enum macros {
    M_DBL0, // double 0
    M_LANG,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   $    |   "  |   «  |   »  |   (  |   )  | Del  |           | Ins  |   @  |   +  |   -  |   /  |   *  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   %    |   B  |   É  |   P  |   O  |   È  |Bkspce|           |CapsLo|   ^  |   V  |   D  |   L  |   J  |   Z    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | W/LSFT |   A  |   U  |   I  |   E  |   ,  |------|           |------|   C  |   T  |   S  |   R  |   N  | M/RSft |
 * |--------+------+------+------+------+------| Tab  |           |      |------+------+------+------+------+--------|
 * | E_CIRC |   À  |   Y  |   X  |   .  |   K  |      |           |      |   '  |   Q  |   G  |   H  |   F  |  Ctrl  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Mirror|L_SYMB| Super| LCtrl| LAlt |                                       |Alt Gr|RCtrl |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                       ,--------------.       ,-------------.
 *                                       |  Esc  |      |       |      |      |
 *                                ,------+-------+------|       |------+------+------.
 *                                |      |       |PgUp  |       |L_SYMB|      |      |
 *                                |Space | LSFT  |------|       |------| RSFT |Enter |
 *                                |      |       |PgDown|       |      |      |      |
 *                                `---------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[LR_BASE] = KEYMAP(  // layer 0 : default
        // left hand
        BP_DLR,     BP_DQOT,   BP_LGIL, BP_RGIL,   BP_LPRN,  KBP_RPRN,KC_DEL,
        BP_PRCENT,  BP_B,      BP_ECUT, BP_P,      BP_O,     BP_EGRV, KC_BSPC,
        SFT_T(BP_W),BP_A,      BP_U,    BP_I,      BP_E,     BP_COMM,
        BP_ECRC,    BP_AGRV,   BP_Y,    BP_X,      BP_DOT,   BP_K,    KC_TAB,
        TG(LR_MIRROR),OSL(LR_NUMFN),KC_LGUI,KC_LCTL, ALT_T(KC_APP),

                                                    KC_ESC,    KC_NO,
                                                             KC_PGUP,
                                          KC_SPC,  KC_BSPC,  KC_PGDN,

        // right hand
        KS_INS,      BP_AT,    BP_PLUS, BP_MINUS,BP_SLASH,BP_ASTR,  BP_EQL,
        KC_CAPSLOCK, BP_DCRC,  BP_V,    BP_D,    BP_L,    BP_J,     BP_Z,
                     BP_C,     BP_T,    BP_S,    BP_R,    BP_N,     SFT_T(BP_M),
        KC_NO,       BP_APOS,  BP_Q,    BP_G,    BP_H,    BP_F,     CTL_T(LCTL(LALT(KC_DEL))),
                             BP_ALGR, M(M_LANG), TG(LR_MEDIA), TG(LR_VIM),LT(LR_SYMB,BP_CCED),

        KC_LEFT, KC_RGHT,
        KC_UP,
        KC_DOWN, KC_ENT,   KC_SPC
    ),
/* Mirror Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    =   |   0  |   9  |   8  |   7  |   6  |   %   |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    Z   |   J  |   L  |   D  |   V  |   ^  |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    M   |   N  |   R  |   S  |   T  |   C  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    Ç   |  F   |   H  |   G  |   Q  |   '  |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |BEPO  |      |      |      |      |                                       |      |      |      |      |       |
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[LR_MIRROR] = KEYMAP(
        // left hand
        BP_EQL,   KC_0,     KC_9,     KC_8,    KC_7,     KC_6,     BP_PERC,
        BP_Z,     BP_J,     BP_L,     BP_D,    BP_V,     BP_DCRC,  KC_TRNS,
        SFT_T(BP_M),BP_N,   BP_R,     BP_S,    BP_T,     BP_C,
        BP_CCED,  BP_F,     BP_H,     BP_G,    BP_Q,     BP_APOS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,      

                                                      KC_TRNS,  KC_TRNS,
                                                                KC_TRNS,
                                             KC_SPC,  KC_TRNS,  KC_TRNS,

        // right hand
        KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                             KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
 /* FN / Numeric Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   F1 |  F2  |   F3 |  F4  |  F5  |      |           |      |   F6 |  F7  |  F8  |  F9  |  F10 |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Home |  Up  | End  | PgUp |      |           |      |      |   7  |  8   |  9   |   *  |  F12   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | Left | Down | Right| PgDn |------|           |------|   =  |   4  |  5   |  6   |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Undo   Cut  | Copy | Paste|   `  |      |           |Enter |      |   1  |  2   |  3   |   -  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |BEPO  |      | Left | Down | Right|                                       |   0  |   00 |   .  |   /  |       |
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[LR_NUMFN] = KEYMAP(
        // left hand
        KC_TRNS,  KC_F1,    KC_F2,    KC_F3,   KC_F4,    KC_F5,    KC_INS,
        KC_TRNS,  BP_DLR,   BP_LPRN,  BP_RPRN, BP_LCBR,  BP_RCBR,  KC_TRNS,
        KC_TRNS,  BP_HASH,  BP_EXLM,  BP_QEST, BP_LBRC,  BP_RBRC,
        KC_TRNS,  BP_PIPE,  KC_HOME,  KC_UP,   KC_END,   BP_GRVB,  KC_ENT,
        KC_TRNS,  BP_AMPR,  KC_LEFT,  KC_DOWN,  KC_RGHT,               

                                                      KC_TRNS,  KC_TRNS,
                                                                KC_TRNS,
                                             KC_SPC,  KC_TRNS,  KC_TRNS,

        // right hand
        KC_PSCR,  KC_F6,     KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11, 
        KC_TRNS,  BP_COLN,   BP_7,     BP_8,     BP_9,     BP_ASTR,  KC_F12,
                  BP_EQL,    BP_4,     BP_5,     BP_6,     BP_PLUS,  KC_RSFT,
        KC_ENT,   BP_SCLN,   BP_1,     BP_2,     BP_3,     BP_MINS,  KC_TRNS,
                             BP_0,     M(M_DBL0),BP_DOT,   BP_SLSH,  KC_TRNS,

        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_PAUS,  KC_TRNS,  KC_TRNS
    ),
};

const uint16_t PROGMEM fn_actions[] = {
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
        case M_DBL0:
            if (record->event.pressed) {
                return MACRO( I(25), T(P0), T(P0), END);
            }    
            break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    return NULL;
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    
    uint8_t layer = biton32(layer_state);
     
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    
    switch (layer) {
        case LR_BASE:
            //ergodox_right_led_1_set(LED_BRIGHTNESS_LO);
            //ergodox_right_led_1_on();
            break;
        case LR_MIRROR:
            ergodox_right_led_1_set(LED_BRIGHTNESS_LO);
            ergodox_right_led_1_on();
            break;
        case LR_SYMB:
            ergodox_right_led_2_set(LED_BRIGHTNESS_LO);
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
};
