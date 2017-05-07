/* OSKTDS
 *
 * I got sick and tired of using my surface without a real on screen interface when my keyboard isn't attached.
 * So I whipped this up in about a day, enjoy!
 * -- GrayHatter, (Probably)
 *
 *  clang -fsanitize=address -g -o osktds main.c -lX11 -lXrender -lXtst -lXi
 *
 */

#include "panel.h"
#include "keys.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/cursorfont.h>
#include <X11/extensions/Xrender.h>
// #include <X11/extensions/XShm.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/XInput2.h>

#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define IN_RECT(mx, my, x, y, w, h) (  (mx) >= (x) \
                                    && (mx) <= (w) \
                                    && (my) >= (y) \
                                    && (my) <= (h) \
                                    )
#define KEY(x) XKeysymToKeycode(display, x)


Display *display;
Screen  *default_screen;
Window  root_window;
Visual  *default_visual;

int default_depth;
int def_screen_num;

GC      gc;
Pixmap  pmap;
Picture render_pic;
Picture color_pic;
XRenderPictFormat *pfmt;

struct OSK {
    // XLib drawing resources
    Window window;
    GC      gc;
    Pixmap  pmap;
    Picture render_pic;
    Picture color_pic;
    XRenderPictFormat *pfmt;

    // current state
    bool hidden;
    int x, y, w, h;

    bool docked;
    bool top;
};


// TODO, don't make this global :/
struct OSK osk = {
    .window = 0,
    .x = 0,
    .y = 1440 - 560,
    .w = 2160,
    .h = 560,

    .docked = true,
    .top    = false,
};

static void key_down(unsigned key)
{
    XTestFakeKeyEvent(display, KEY(key), true, 0);
}

static void key_up(unsigned key)
{
    XTestFakeKeyEvent(display, KEY(key), false, 0);
}


static void key_send(uint c)
{
    key_down(c);
    key_up(c);
}

static void draw_box(int x, int y, int w, int h, uint32_t color)
{
    XSetForeground(display, gc, color);
    XDrawRectangle(display, pmap, gc, x, y, w - 1, h -1);
}

static void draw_box_fill(int x, int y, int w, int h, uint32_t color)
{
    XSetForeground(display, gc, color);
    XFillRectangle(display, pmap, gc, x, y, w, h);
}

static bool osk_hide(PANEL *p)
{
    (void)p;
    if (osk.hidden) {
        XResizeWindow(display, osk.window, 2160, 560);
    } else {
        XResizeWindow(display, osk.window, 40, 80);
    }
    osk.hidden = !osk.hidden;
    return true;
}
PANEL btn_hide = {
    .x = 0,
    .y = 0,
    .w = 80,
    .h = 80,

    .type = OSKTDS_PANEL_TYPE_BUTTON,
    .enabled = true,
    .draw_func = NULL,
    .mdown_func = osk_hide,

    .child = (PANEL*[]) {
        NULL,
    }

};

static void pdraw_sidebar_l(PANEL *p, int x, int y, int w, int h)
{
    draw_box(x,      y, w, 80, ~0);
    draw_box(x, h - 80, w, 80, ~0);
}
PANEL sidebar_l = {
    .x = 0,
    .y = 0,
    .w = 80,
    .h = 0,

    .type = 0,
    .enabled = true,
    .draw_func = pdraw_sidebar_l,

    .child = (PANEL*[]) {
        &btn_hide,
        NULL,
    }
};

static bool osk_jump(Window w, bool up)
{
    osk.docked = true;
    if (up) {
        osk.top = true;
        XMoveWindow(display, w, 0, 0);
    } else {
        osk.top = false;
        XMoveWindow(display, w, 0, 1440 - osk.h);
    }
    return true;
}

static bool osk_jump_up(PANEL *w)
{
    return osk_jump(osk.window, 1);
}

static bool osk_jump_dn(PANEL *w)
{
    return osk_jump(osk.window, 0);
}

PANEL jump_btn_up = {
    .x = 0,
    .y = 0,
    .w = 80,
    .h = 280,

    .type = 0,
    .enabled = true,
    .draw_func = NULL,
    .mdown_func = osk_jump_up,

    .child = (PANEL*[]) {
        NULL,
    }
}, jump_btn_dn = {
    .x = 0,
    .y = 280,
    .w = 80,
    .h = 280,

    .type = 0,
    .enabled = true,
    .draw_func = NULL,
    .mdown_func = osk_jump_dn,

    .child = (PANEL*[]) {
        NULL,
    }
};

static void pdraw_sidebar_r(PANEL *p, int x, int y, int w, int h)
{
    if (osk.top) {
        draw_box(x, h / 2, w,     h, ~0);
    } else {
        draw_box(x,     y, w, h / 2, ~0);
    }
}
PANEL sidebar_r = {
    .x = -80,
    .y = 0,
    .w = 80,
    .h = 0,

    .type = 0,
    .enabled = true,
    .draw_func = pdraw_sidebar_r,

    .child = (PANEL*[]) {
        &jump_btn_up,
        &jump_btn_dn,
        NULL,
    }
};

PANEL kb_layout_dvorak_r1 ={
    .x = 150,
    .y = 10,
    .w = 0,
    .h = 120,

    .type = OSKTDS_PANEL_TYPE_KEY_ROW,
    .enabled = true,
    .draw_func = NULL,

    .child = (PANEL*[]) {
        &OSK_key_squote,
        &OSK_key_comma,
        &OSK_key_period,
        &OSK_key_p,
        &OSK_key_y,
        &OSK_key_f,
        &OSK_key_g,
        &OSK_key_c,
        &OSK_key_r,
        &OSK_key_l,
        &OSK_key_bksp,
        NULL,
    }
};

PANEL kb_layout_dvorak_r2 ={
    .x = 180,
    .y = 150,
    .w = 0,
    .h = 120,

    .type = OSKTDS_PANEL_TYPE_KEY_ROW,
    .enabled = true,
    .draw_func = NULL,

    .child = (PANEL*[]) {
        &OSK_key_a,
        &OSK_key_o,
        &OSK_key_e,
        &OSK_key_u,
        &OSK_key_i,
        &OSK_key_d,
        &OSK_key_h,
        &OSK_key_t,
        &OSK_key_n,
        &OSK_key_s,
        &OSK_key_enter,
        NULL,
    }
};

PANEL kb_layout_dvorak_r3 ={
    .x = 10,
    .y = 290,
    .w = 0,
    .h = 120,

    .type = OSKTDS_PANEL_TYPE_KEY_ROW,
    .enabled = true,
    .draw_func = NULL,

    .child = (PANEL*[]) {
        &OSK_key_shift_l,
        &OSK_key_semicolon,
        &OSK_key_q,
        &OSK_key_j,
        &OSK_key_k,
        &OSK_key_x,
        &OSK_key_b,
        &OSK_key_m,
        &OSK_key_w,
        &OSK_key_v,
        &OSK_key_z,
        &OSK_key_shift_r,
        NULL,
    }
};

PANEL kb_layout_dvorak_r4 ={
    .x = 400,
    .y = 430,
    .w = 0,
    .h = 120,

    .type = OSKTDS_PANEL_TYPE_KEY_ROW,
    .enabled = true,
    .draw_func = NULL,

    .child = (PANEL*[]) {
        &OSK_key_space,
        NULL,
    }
};

static void pdraw_layout_dvorak_min(PANEL *p, int x, int y, int w, int h)
{
    int e = h / 4;
    draw_box(x, y + e * 0, w, e, 0x00FFFF);
    draw_box(x, y + e * 1, w, e, 0xFF00FF);
    draw_box(x, y + e * 2, w, e, 0xFFFF00);
    draw_box(x, y + e * 3, w, e, 0xFF0000);
}
PANEL kb_layout_dvorak_min ={
    .x = 0,
    .y = 0,
    .w = 0,
    .h = 0,

    .type = 0,
    .enabled = true,
    .draw_func = pdraw_layout_dvorak_min,

    .child = (PANEL*[]) {
        &kb_layout_dvorak_r1,
        &kb_layout_dvorak_r2,
        &kb_layout_dvorak_r3,
        &kb_layout_dvorak_r4,
        NULL,
    }
};

static void pdraw_layout_dvorak_full(PANEL *p, int x, int y, int w, int h)
{
    int e = h / 3;
    draw_box(x,         y, w, e, 0xFFFF00);
    draw_box(x,     y + e, w, e, 0xFF00FF);
    draw_box(x, y + e + e, w, e, 0x00FFFF);
}
PANEL kb_layout_dvorak_full = {
    .x = 0,
    .y = 0,
    .w = 0,
    .h = 0,

    .type = 0,
    .enabled = false,
    .draw_func = pdraw_layout_dvorak_full,

    .child = (PANEL*[]) {
        &kb_layout_dvorak_r1,
        &kb_layout_dvorak_r2,
        &kb_layout_dvorak_r3,
        NULL,
    }
};

static void pdraw_center(PANEL *p, int x, int y, int w, int h)
{
    draw_box(x, y, w, h, 0x00FFFF);
}
PANEL center_tree = {
    .x = 80,
    .y = 0,
    .w = -80,
    .h = 0,

    .type = 0,
    .enabled = true,
    .draw_func = pdraw_center,

    .child = (PANEL*[]) {
        &kb_layout_dvorak_min,
        NULL,
    }
};

static void pdraw_root(PANEL *p, int x, int y, int w, int h)
{
    draw_box_fill(x, y, w, h, 0);
}
PANEL root_tree = {
    .x = 0,
    .y = 0,
    .w = 0,
    .h = 0,

    .type = 0,
    .enabled = true,
    .draw_func = pdraw_root,

    .child = (PANEL*[]) {
        &sidebar_l,
        &center_tree,
        &sidebar_r,
        NULL,
    }
};

static void xlib_init(void)
{
    if ((display = XOpenDisplay(NULL)) == NULL) {
        exit(-2);
    }

    default_screen = DefaultScreenOfDisplay(display);
    default_visual = DefaultVisual(display, def_screen_num);
    root_window    = RootWindow(display, def_screen_num);

    default_depth  = DefaultDepth(display, def_screen_num);
    def_screen_num = DefaultScreen(display);
}

static void draw_push(Window win)
{
    XCopyArea(display, pmap, win, gc, 0, 0, osk.w, osk.h, 0, 0);
}

static void draw_key_row(PANEL *row, int x, int y, int w, int h)
{
    if (row->child) {
        PANEL *key = NULL;
        PANEL **keys = row->child;
        while (*keys) {
            key = *keys++;

            uint32_t color = key->m_over ? 0xAAAAAA : 0x888888;
            draw_box_fill(x, y, key->w, key->h, color);
            x += key->w + 10; // positon + padding
        }
    }
}

static void draw_tree_core(PANEL *p, int x, int y, int w, int h)
{
    if (!p->enabled) {
        return;
    }

    x = p->x >= 0 ? x + p->x : x + (w + p->x);
    y = p->y >= 0 ? y + p->y : y + (h + p->y);

    w = p->w >  0 ? p->w : w + p->w - p->x;
    h = p->h >  0 ? p->h : h + p->h - p->y;

    if (p->draw_func) {
        p->draw_func(p, x, y, w, h);
    }

    if (p->type == OSKTDS_PANEL_TYPE_KEY_ROW) {
        draw_key_row(p, x, y, w, h);
    }

    if (p->child) {
        PANEL **children = p->child;
        while (*children) {
            PANEL *child = *children++;
            draw_tree_core(child, x, y, w, h);
        }
    }
}

static void draw_tree(PANEL *p, int x, int y, int w, int h)
{
    draw_tree_core(p, x, y, w, h);
    draw_push(osk.window);
}

static void draw_pixel(int x, int y, uint32_t color)
{
    XSetForeground(display, gc, ~color);
    XDrawLine(display, pmap, gc, x - 1, y -1, x + 2, y + 2);

    XSetForeground(display, gc, color);
    XDrawLine(display, pmap, gc, x, y, x, y);
}

static bool mouse_down_row(PANEL *row, int touch_id)
{
    if (row->child) {
        PANEL *key = NULL;
        PANEL **keys = row->child;
        while (*keys) {
            key = *keys++;

            if (key->m_over && key->type_data) {
                key_send(key->type_data);
                printf("m down on type_data %c\n", (char)key->type_data);
                return true;
            }
        }
    }

    return false;
}

static bool mouse_down_core(PANEL *p, int touch_id)
{
    if (!p->enabled || !p->m_over) {
        return false;
    }

    if (p->child) {
        PANEL **children = p->child;
        while (*children) {
            PANEL *child = *children++;
            if (mouse_down_core(child, touch_id)) {
                return true;
            }
        }
    }

    if (p->type == OSKTDS_PANEL_TYPE_KEY_ROW) {
        return mouse_down_row(p, touch_id);
    }

    if (p->mdown_func) {
        return p->mdown_func(p);
    }

    return false;
}

static void mouse_down(PANEL *p, int touch_id)
{
    mouse_down_core(p, touch_id);
}

static void mouse_up(PANEL *p, int touch_id)
{
    // mouse_up_core(p, touch_id);
}

static void mouse_move_row(PANEL *row, int x, int y, int w, int h, int mx, int my, int touch_id)
{
    if (row->child) {
        int real_w = x;
        PANEL *key = NULL;
        PANEL **keys = row->child;
        while (*keys) {
            key = *keys++;
            key->m_over = false;
            key->m_over_tid = 0;
            real_w += key->w;

            if (IN_RECT(mx, my, x, y, real_w, y + key->h)) {
                key->m_over = true;
                key->m_over_tid = touch_id;
            }
            real_w += 10;
            x = real_w;
        }
    }
}

static void mouse_move_core(PANEL *p, int x, int y, int w, int h, int mx, int my, int touch_id)
{
    if (!p->enabled || p->type == OSKTDS_PANEL_TYPE_KEY) {
        return;
    }
    p->m_over = false;

    if (p->child) {
        PANEL **children = p->child;
        while (*children) {
            PANEL *child = *children++;

            int real_x = child->x >= 0 ? x + child->x : x + (w + child->x);
            int real_y = child->y >= 0 ? y + child->y : y + (h + child->y);

            int real_w = child->w > 0 ? child->w + real_x : w - abs(child->w);
            int real_h = child->h > 0 ? child->h + real_y : h - abs(child->h);

            mouse_move_core(child, real_x, real_y, real_w, real_h, mx, my, touch_id);

            if (IN_RECT(mx, my, real_x, real_y, real_w, real_h)) {
                child->m_over = true;
            }

            if (p->type == OSKTDS_PANEL_TYPE_KEY_ROW) {
                mouse_move_row(p, real_x, real_y, real_w, real_h, mx, my, touch_id);
            }
        }
    }
}

static void mouse_move(PANEL *p, int x, int y, int w, int h, int mx, int my, int touch_id)
{
    mouse_move_core(p, x, y, w, h, mx, my, touch_id);
    p->m_over = true; // We don't care when it's not
}

static int xevent(XEvent *ev)
{
    switch (ev->type) {
        case KeyPress: {
            // printf("KeyPress\n");
            return true;
        }

        case KeyRelease: {
            // printf("KeyRelease\n");
            return true;
        }

        case ButtonPress: {
            // printf("ButtonPress\n");
            XButtonEvent *bev = &ev->xbutton;
            mouse_move(&root_tree, 0, 0, osk.w, osk.h, bev->x, bev->y, 0);
            mouse_down(&root_tree, 0);

            if (bev->x >= osk.w - 80) {
                osk_jump(bev->window, bev->y <= osk.h / 2);
                return true;
            }

            if (bev->x <= 80 && bev->y >= osk.h - 80) {
                // exit command
                return -1;
            }

            return true;
        }

        case ButtonRelease: {
            // printf("ButtonRelease\n");
            XButtonEvent *bev = &ev->xbutton;
            mouse_move(&root_tree, 0, 0, osk.w, osk.h, bev->x, bev->y, 0);
            mouse_up(&root_tree, 0);
            return true;
        }

        case MotionNotify: {
            // printf("Motion %i, %i \n", ev->xmotion.x, ev->xmotion.y);
            mouse_move(&root_tree, 0, 0, osk.w, osk.h, ev->xmotion.x, ev->xmotion.y, 0);
            return true;
        }

        case EnterNotify: {
            // printf("EnterNotify\n");
            return false;
        }

        case LeaveNotify: {
            // printf("LeaveNotify\n");
            return true;
        }

        case FocusIn: {
            // printf("FocusIn\n");
            return true;
        }

        case FocusOut: {
            // printf("FocusOut\n");
            return true;
        }

        case Expose: {
            // printf("Expose\n");
            return true;
        }

        case MapNotify: {
            // printf("MapNotify\n");
            return true;
        }

        case MappingNotify: {
            // printf("MapNotify\n");
            return true;
        }

        case NoExpose: {
            // printf("NoExpose\n");
            return true;
        }

        case GenericEvent: {
            // Probably a touchscreen event
            if (XGetEventData(display, (XGenericEventCookie*)ev)) {
                XGenericEventCookie *cookie = &ev->xcookie;
                XIDeviceEvent *touch = cookie->data;
                XITouchOwnershipEvent *own = cookie->data;
                switch (cookie->evtype) {
                    case XI_TouchBegin: {
                        printf("touch begin  touch_id %02i device_id %04i source_id %u  event xy %04f %04f \n",
                                touch->detail, touch->deviceid, touch->sourceid, touch->event_x, touch->event_y);
                        mouse_move(&root_tree, 0, 0, osk.w, osk.h, touch->event_x, touch->event_y, touch->detail);
                        mouse_down(&root_tree, touch->detail);
                        break;
                    }
                    case XI_TouchUpdate: {
                        printf("touch update touch_id %02i device_id %04i source_id %u  event xy %04f %04f \n",
                                touch->detail, touch->deviceid, touch->sourceid, touch->event_x, touch->event_y);
                        mouse_move(&root_tree, 0, 0, osk.w, osk.h, touch->event_x, touch->event_y, touch->detail);
                        break;
                    }
                    case XI_TouchEnd: {
                        printf("touch end    touch_id %02i device_id %04i source_id %u  event xy %04f %04f \n",
                                touch->detail, touch->deviceid, touch->sourceid, touch->event_x, touch->event_y);
                        mouse_move(&root_tree, 0, 0, osk.w, osk.h, touch->event_x, touch->event_y, touch->detail);
                        mouse_up(&root_tree, touch->detail);
                        break;
                    }
                    case XI_TouchOwnership: {
                        printf("Ownership \n");
                        printf("touch_id %04i device_id %04i source_id %u type %02i\n",
                               own->touchid, own->deviceid, own->sourceid, own->evtype);
                        break;
                    }
                    default: {
                        printf("Unknown cookie event\n");
                        break;
                    }
                }

                XFreeEventData(display, (XGenericEventCookie*)ev);
            }
            return true;
        }

        default: {
            printf("Event Type: %u\n", ev->type);
            return false;
        }
    }

    printf("End of event -_- \n");
    return false;
}

static Window window_init(void)
{
    XVisualInfo xvinfo;
    XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &xvinfo);

    XSetWindowAttributes attrib = {
        .colormap           = XCreateColormap(display, DefaultRootWindow(display), xvinfo.visual, AllocNone),
        .border_pixel       = 0,
        .background_pixel   = 0,
        .override_redirect  = true,
        .event_mask         = ExposureMask    | EnterWindowMask   | LeaveWindowMask   | FocusChangeMask |
                              ButtonPressMask | ButtonReleaseMask | PointerMotionMask |
                              KeyPressMask    | KeyReleaseMask,
    };

    Window win = XCreateWindow(display, DefaultRootWindow(display), osk.x, osk.y, osk.w, osk.h, 0,
                               xvinfo.depth, InputOutput, xvinfo.visual,
                               CWColormap | CWBackPixmap | CWBorderPixel | CWEventMask | CWOverrideRedirect,
                               &attrib);

    XSizeHints size_hints = {
        .flags       = PPosition | PBaseSize | PMinSize | PMaxSize | PWinGravity,
        .x           = osk.x,
        .y           = osk.y,
        .base_width  = osk.w,
        .base_height = osk.h,
        .min_width   = osk.w,
        .min_height  = osk.h,
        .max_width   = osk.w * 4,
        .max_height  = osk.h * 4,
        .win_gravity = SouthWestGravity,
    };

    XWMHints wm_hints = {
        .flags         = StateHint | InputHint | WindowGroupHint,
        .initial_state = NormalState,
        .input         = true,
        .window_group  = win,
    };

    XClassHint class_hints = {
        .res_name   = "osktds",
        .res_class  = "osktds",
    };

    XSetWMProperties(display, win, NULL, NULL, NULL, 0, &size_hints, &wm_hints, &class_hints);

    Atom a_type = XInternAtom(display, "_NET_WM_WINDOW_TYPE", 0);
    Atom a_util = XInternAtom(display, "_NET_WM_WINDOW_TYPE_UTILITY", 0);
    XChangeProperty(display, win, a_type, XA_ATOM, 32, PropModeReplace, (uint8_t *)&a_util, 1);

    Atom list[] = {
        XInternAtom(display, "WM_DELETE_WINDOW", 0),
        // XInternAtom(display, "WM_TAKE_FOCUS", 0),
    };
    XSetWMProtocols(display, win, list, 1);

    pmap = XCreatePixmap(display, win, osk.w, osk.h, xvinfo.depth);
    gc = XCreateGC(display, win, 0, 0);
    XSetGraphicsExposures(display, gc, false);

    pfmt = XRenderFindVisualFormat(display, xvinfo.visual);

    /* Xft draw context/color */
    render_pic = XRenderCreatePicture(display, pmap, pfmt, 0, NULL);

    XRenderColor xrcolor = { 0,0,0,0 };
    color_pic = XRenderCreateSolidFill(display, &xrcolor);

    return win;
}

void xlib_query_devices(void)
{
    int ndevices;
    XIDeviceInfo *info = XIQueryDevice(display, XIAllDevices, &ndevices);

    for (int i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];
        printf("Device name %s\n", dev->name);
        for (int j = 0; j < dev->num_classes; j++) {
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo*)class;

            if (class->type != XITouchClass) {
                continue;
            }

            printf("    %s touch device, supporting %d touches.\n",
                   (t->mode == XIDirectTouch) ?  "direct" : "dependent",
                   t->num_touches);
        }
    }
}

void xlib_touch_init(void)
{
    XIEventMask mask;

    memset(&mask, 0, sizeof(XIEventMask));
    mask.deviceid = XIAllMasterDevices;
    mask.mask_len = XIMaskLen(XI_LASTEVENT);
    mask.mask = (unsigned char*) calloc(mask.mask_len, sizeof(char));

    XISetMask(mask.mask, XI_TouchOwnership);
    XISetMask(mask.mask, XI_TouchBegin);
    XISetMask(mask.mask, XI_TouchUpdate);
    XISetMask(mask.mask, XI_TouchEnd);

    XISelectEvents(display, osk.window, &mask, 1);

    free(mask.mask);
}

int main (void) {
    xlib_init();
    osk.window = window_init();

    xlib_query_devices();
    xlib_touch_init();

    XIM xim;
    if ((xim = XOpenIM(display, 0, 0, 0)) == NULL) {
        return -3;
    }

    XIC xic = NULL;
    if (xim) {
        if ((xic = XCreateIC(xim, XNInputStyle,
                             XIMPreeditNothing | XIMStatusNothing,
                             XNClientWindow, osk.window, XNFocusWindow, osk.window, NULL))) {
            XSetICFocus(xic);
        } else {
            XCloseIM(xim);
            xim = 0;
        }
    }

    XMapWindow(display, osk.window);

    /* event loop */
    while (true) {
        XEvent event;
        XNextEvent(display, &event);

        int r = xevent(&event);
        if (r < 0) {
            break;
        } else if (r) {
            draw_tree(&root_tree, 0, 0, osk.w, osk.h);
        }

        if (XPending(display)) {
            continue;
        }
    }

    return 0;
}
