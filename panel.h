#ifndef OSKTDS_PANEL_H
#define OSKTDS_PANEL_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    OSKTDS_PANEL_TYPE_NONE,

    OSKTDS_PANEL_TYPE_BOX,
    OSKTDS_PANEL_TYPE_LAYOUT,

    OSKTDS_PANEL_TYPE_KEY_ROW,
    OSKTDS_PANEL_TYPE_KEY,

    OSKTDS_PANEL_TYPE_BUTTON,
    OSKTDS_PANEL_TYPE_MODAL,
    OSKTDS_PANEL_TYPE_NOS,
} OSKTDS_PANEL_TYPE;

typedef struct panel PANEL;
struct panel {
    int x;
    int y;
    int w;
    int h;

    OSKTDS_PANEL_TYPE type;
    uint64_t type_data;

    // Status
    bool enabled;
    void (*draw_func)(PANEL *, int, int, int, int);

    bool m_over;
    int m_over_tid;
    bool (*mdown_func)(PANEL *);

    PANEL **child;
};

#endif // OSKTDS_PANEL_H
