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
    LR_SYMB, // YMB and mumeric keyboard
    LR_VIM, // QWERTY vim layer
    LR_MEDIA, // media layer
};

enum macros {
    M_DBL0, // double 0
    M_LANG,
    M_VIQW, //Switch between pure QWERTY and VI actions
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   |   "  |   «  |   »  |   (  |   )  |  $   |           |  %   |   @  |   +  |   -  |   /  |   *  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   B  |   É  |   P  |   O  |   È  |  W   |           |  L1  |   ^  |   V  |   D  |   L  |   J  |   Z    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   A  |   U  |   I  |   E  |   ,  |------|           |------|   C  |   T  |   S  |   R  |   N  | M/RSft |
 * |--------+------+------+------+------+------|Enter |           |BkSpce|------+------+------+------+------+--------|
 * |  Ctrl  |   À  |   Y  |   X  |   .  |   K  |      |           |      |   '  |   Q  |   G  |   H  |   F  |  Ctrl  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Mirror| Cut  | Copy | Paste| LAlt |                                       |Alt Gr|AltSft|Media | Vim  | Ç/~L1|
 *   `----------------------------------'                                       `----------------------------------'
 *                                       ,--------------.       ,-------------.
 *                                       |  Del  | GUI  |       | Left | Right|
 *                                ,------+-------+------|       |------+------+------.
 *                                |      |       |PgUp  |       | Up   |      |      |
 *                                |Space |Bkspce |------|       |------|Enter |Space |
 *                                |      |       |PgDown|       | Down |      |      |
 *                                `---------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[LR_BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,     KC_1,      KC_2,    KC_3,      KC_4,     KC_5,    BP_DLR,
        KC_TAB,     BP_B,      BP_ECUT, BP_P,      BP_O,     BP_EGRV, BP_W,  
        KC_LSFT,    BP_A,      BP_U,    BP_I,      BP_E,     BP_COMM,
        KC_LCTL,    BP_AGRV,   BP_Y,    BP_X,      BP_DOT,   BP_K,    KC_ENT,
        TG(LR_MIRROR),S(KC_DELT),LCTL(KC_INS),S(KC_INS), ALT_T(KC_APP),

                                                   KC_DELT,  KC_LGUI,
                                                             KC_PGUP,
                                          KC_SPC,  KC_BSPC,  KC_PGDN,

        // right hand
        BP_PERC,   KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     BP_EQL,
        TG(LR_SYMB), BP_DCRC,  BP_V,    BP_D,    BP_L,    BP_J,     BP_Z,
                   BP_C,     BP_T,    BP_S,    BP_R,    BP_N,     SFT_T(BP_M),
        KC_BSPC,   BP_APOS,  BP_Q,    BP_G,    BP_H,    BP_F,     CTL_T(LCTL(LALT(KC_DEL))),
                             BP_ALGR, M(M_LANG), TG(LR_MEDIA), TG(LR_VIM),LT(LR_SYMB,BP_CCED),

        KC_LEFT, KC_RGHT,
        KC_UP,
        KC_DOWN, KC_ENT,   KC_SPC
    ),
/* Mirror Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    =   |   0  |   9  |   8  |   7  |   6  |   %  |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    Z   |   J  |   L  |   D  |   V  |   ^  |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    M   |   N  |   R  |   S  |   T  |   C  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    Ç   |  F   |   H  |   G  |   Q  |   '  |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |       |
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
 * |        |   F1 |  F2  |   F3 |  F4  |  F5  |Insert|           | Print|   F6 |  F7  |  F8  |  F9  |  F1  |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   $  |   (  |   )  |   {  |   }  |      |           |      |   :  |   7  |  8   |  9   |   *  |  F12   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   !  |   ?  |   [  |   ]  |------|           |------|   =  |   4  |  5   |  6   |   +  | RShift |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  |   | Home |  Up  |  End |   `  | Enter|           |Enter |   ;  |   1  |  2   |  3   |   -  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Pause |  &   | Left | Down | Right|                                       |   0  |   00 |   .  |   /  |       |
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[LR_SYMB] = KEYMAP(
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
 /* Vim / QWERTY Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |    1 |   2  |    3 |   4  |   5  |      |           |      |    6 |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |  I   |  O   |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | MO(SFT)|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |  K   |  L   |   ;  | MO(SFT)|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |  ,   |  .   |   /  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Vi/QW |      |      |      |      |                                       |      |      |      |      |       |
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[LR_VIM] = KEYMAP(
        // left hand
        KC_TRNS,  BP_1,     BP_2,     BP_3,    BP_4,     BP_5,     KC_TRNS,
        KC_TRNS,  BP_Q,     BP_W,     BP_E,    BP_R,     BP_T,     KC_TRNS,
        KC_TRNS,  BP_A,     BP_S,     BP_D,    BP_F,     BP_G,   
        KC_TRNS,  BP_Z,     BP_X,     BP_C,    BP_V,     BP_B,     KC_TRNS,
        M(M_VIQW),  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,                

                                                      KC_TRNS,  KC_TRNS,
                                                                KC_TRNS,
                                             KC_SPC,  KC_TRNS,  KC_TRNS,

        // right hand
        KC_TRNS,  BP_6,      BP_7,     BP_8,     BP_9,     BP_0,     KC_TRNS,
        KC_TRNS,  BP_Y,      BP_U,     BP_I,     BP_O,     BP_P,     KC_TRNS,
                  BP_H,      BP_J,     BP_K,     BP_L,     KC_SCLN,  KC_TRNS,
        KC_TRNS,  BP_N,      BP_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_TRNS,
                             KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

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
        case LR_VIM:
            ergodox_right_led_3_set(LED_BRIGHTNESS_LO);
            ergodox_right_led_3_on();
        default:
            // none
            break;
    }
};
