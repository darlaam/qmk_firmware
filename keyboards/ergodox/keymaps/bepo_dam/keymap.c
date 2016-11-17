/* Bépo keymap  */
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "keymap_bepo.h"
#include "led.h"

#define LEADER_TIMEOUT 200

enum layers {
    LR_BASE, // default bépo layer
    LR_MIRROR, // mirror layer (left hand mode)
    LR_NUMFN, // SYMB and mumeric keyboard
};

enum macros {
    M_DBL0, // double 0
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
 * | E_CIRC |   À  |   Y  |   X  |   .  |   K  |      |           |      |   '  |   Q  |   G  |   H  |   F  | C_CED  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Mirror|L_SYMB| Super| LCtrl| LAlt |                                       |Alt Gr|RCtrl |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                       ,--------------.       ,-------------.
 *                                       |  Esc  |      |       |      |      |
 *                                ,------+-------+------|       |------+------+------.
 *                                |      |       |PgUp  |       |L_SYMB|      |      |
 *                                |Space | LSFT  |------|       |------| RSFT |Enter |
 *                                |      |       |PgDown|       | LEAD |      |      |
 *                                `---------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[LR_BASE] = KEYMAP(  // layer 0 : default
        // left hand
        BP_DLR,       BP_DQOT,      BP_LGIL,      BP_RGIL,      BP_LPRN,      BP_RPRN,      KC_DEL,
        BP_PERC,      BP_B,         BP_ECUT,      BP_P,         BP_O,         BP_EGRV,      KC_BSPC,
        SFT_T(BP_W),  BP_A,         BP_U,         BP_I,         BP_E,         BP_COMM,
        BP_ECRC,      BP_AGRV,      BP_Y,         BP_X,         BP_DOT,       BP_K,         KC_TAB,
        TG(LR_MIRROR),OSL(LR_NUMFN),KC_LGUI,      KC_LCTL,      ALT_T(KC_APP),

                                                                              KC_ESC,       KC_NO,
                                                                                            KC_PGUP,
                                                                KC_SPC,       KC_LSFT,      KC_PGDN,

        // right hand
        KC_INS,       BP_AT,        BP_PLUS,      BP_MINUS,     BP_SLASH,     BP_ASTR,      BP_EQL,
        KC_CAPSLOCK,  BP_DCRC,      BP_V,         BP_D,         BP_L,         BP_J,         BP_Z,
                      BP_C,         BP_T,         BP_S,         BP_R,         BP_N,         SFT_T(BP_M),
        KC_NO,        BP_APOS,      BP_Q,         BP_G,         BP_H,         BP_F,         BP_CCED,
                                    BP_ALGR,      KC_RCTL,      KC_NO,        KC_NO,        KC_NO,

        KC_NO,        KC_NO,
        TG(LR_NUMFN),
        KC_LEAD,      KC_RSFT,      KC_ENT
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
[LR_MIRROR] = KEYMAP(  // layer 1 : Mirror
        // left hand
        BP_EQL,       BP_ASTR,      BP_SLASH,     BP_MINUS,     BP_PLUS,      BP_AT,        KC_INS,
        BP_Z,         BP_J,         BP_L,         BP_D,         BP_V,         BP_DCRC,      KC_NO,
        SFT_T(BP_M),  BP_N,         BP_R,         BP_S,         BP_T,         BP_C,
        BP_CCED,      BP_F,         BP_H,         BP_G,         BP_Q,         BP_APOS,      KC_NO,
        KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_RCTL,      BP_ALGR,

                                                                              KC_ESC,       KC_NO,
                                                                                            KC_PGUP,
                                                                KC_SPC,       KC_LSFT,      KC_PGDN,

        // right hand
        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                      KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                    KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,

        KC_NO,        KC_NO,
        TG(LR_NUMFN),
        KC_NO,        KC_RSFT,      KC_ENT
    ),
 /* FN / Numeric Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   F1 |  F2  |   F3 |  F4  |  F5  |      |           |      |   F6 |  F7  |  F8  |  F9  |  F10 |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Home |  Up  | End  | PgUp |      |           |      |      |   7  |  8   |  9   |   *  |  F12   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | Left | Down | Right| PgDn |------|           |------|      |   4  |  5   |  6   |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Undo   Cut  | Copy | Paste|   `  |      |           |      |      |   1  |  2   |  3   |   -  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |BEPO  |      |      |      |      |                                       |   0  |   00 |   .  |   /  |       |
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[LR_NUMFN] = KEYMAP(  // layer 1 : Function and numeric
        // left hand
        KC_NO,        KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,        KC_MUTE,
        KC_NO,        KC_NO,        KC_HOME,      KC_UP,        KC_END,       KC_PGUP,      KC_VOLU,
        KC_NO,        KC_NO,        KC_LEFT,      KC_DOWN,      KC_RIGHT,     KC_PGDN,
        //KC_NO,        KC_UNDO,      KC_CUT,       KC_COPY,      KC_PASTE,     KC_NO,        KC_VOLD,
        KC_NO,        KC_NO,        S(KC_DELT),   LCTL(KC_INS), S(KC_INS),    KC_NO,        KC_VOLD,
	KC_NO,        KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,

                                                                              KC_ESC,       KC_NO,
                                                                                            KC_NO,
                                                                KC_TRNS,      KC_TRNS,      KC_NO,

        // right hand
        KC_NO,        KC_F6,        KC_F7,        KC_F8,        KC_F9,        KC_F10,       KC_F11,
        KC_NO,        KC_NO,        KC_P7,        KC_P8,        KC_P9,        KC_PAST,      KC_F12,
                      KC_PEQL,      KC_P4,        KC_P5,        KC_P6,        KC_PPLS,      KC_NO,
        KC_NO,        KC_NO,        KC_P1,        KC_P2,        KC_P3,        KC_PMNS,      KC_NO,
                                    KC_P0,        M(M_DBL0),    KC_PDOT,      KC_PSLS,      KC_NO,

        KC_NO,        KC_NO,
        KC_TRNS,
        KC_NO,        KC_TRNS,      KC_KP_ENTER
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
};


LEADER_EXTERNS();

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
      leading = false;
      leader_end();

      SEQ_ONE_KEY(BP_Y) {
        register_code(KC_LSFT);
        register_code(KC_DELT);
        unregister_code(KC_LSFT);
        unregister_code(KC_DELT);
      }
    }
    
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
        case LR_NUMFN:
            ergodox_right_led_2_set(LED_BRIGHTNESS_LO);
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
};
