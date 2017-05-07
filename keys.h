#ifndef OSKTDS_KEYS_H
#define OSKTDS_KEYS_H

#include "panel.h"

#include <stddef.h>

#define XK_MISCELLANY 1
#include <X11/keysymdef.h>

#define OSKTDS_KEYSIZE 120 // TODO don't hardcode 480/3

PANEL
OSK_key_0 = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_1 = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_2 = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_3 = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_4 = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_5 = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_6 = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_7 = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_8 = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

},
OSK_key_9 = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},

OSK_key_a = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'a',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_b = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'b',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_c = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'c',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_d = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'd',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_e = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'e',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_f = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'f',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_g = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'g',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_h = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'h',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_i = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'i',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_j = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'j',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_k = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'k',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_l = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'l',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_m = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'm',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_n = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'n',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_o = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'o',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_p = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'p',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_q = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'q',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_r = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'r',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_s = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 's',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_t = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 't',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_u = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'u',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_v = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'v',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_w = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'w',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_x = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'x',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_y = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'y',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_z = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 'z',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},


OSK_key_bksp = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE * 2,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = XK_BackSpace,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_enter = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE * 2,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = XK_Return,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_shift = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE * 2,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = XK_Shift_L,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_shift_l = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE * 2,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = XK_Shift_L,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_shift_r = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE * 2,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = XK_Shift_R,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_space = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE * 6,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = ' ',

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_period = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_comma  = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_semicolon  = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_fslash = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_bslash = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_squote = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_dquote = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_sdash = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_ddash = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_emark = {
    .x = 0,
    .y = 0,
    .w = OSKTDS_KEYSIZE,
    .h = OSKTDS_KEYSIZE,

    .type = OSKTDS_PANEL_TYPE_KEY,
    .type_data = 0,

    .enabled = true,
    .draw_func = NULL,

    .mdown_func = NULL,

    .child = NULL,
},
OSK_key_qmark = {};


#endif // OSKTDS_KEYS_H
