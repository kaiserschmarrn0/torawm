#include "araiwm.h"

/* attributes */

#define NUM_WS 4

#define TOP 0
#define BOT 28
#define GAP 0
#define BORDER 0

#define TITLE 16

#define FOCUSCOL 0x4d484a
#define UNFOCUSCOL 0x302e2f

#define SNAP_MARGIN 5
#define SNAP_CORNER 256

//ignore gaps when maxed
#define SNAP_MAX_SMART

/* keyboard modifiers */

#define MOD XCB_MOD_MASK_4
#define SHIFT XCB_MOD_MASK_SHIFT

/* mouse controls */

static const button grab_buttons[] = {
	{ MOD, XCB_BUTTON_INDEX_1, mouse_move   },
	{ MOD, XCB_BUTTON_INDEX_3, mouse_resize },
};

static const button parent_buttons[] = {
	{ 0, XCB_BUTTON_INDEX_1, mouse_move   },
	{ 0, XCB_BUTTON_INDEX_3, mouse_resize },
};

/* keyboard controls */

static const keybind keys[] = {
	{ MOD,         XK_q,     close,     0 },
	{ MOD,         XK_Tab,   cycle,     0 },
	{ MOD,         XK_Left,  snap_l,    0 },
	{ MOD,         XK_Right, snap_r,    0 },
	{ MOD,         XK_f,     snap_max,  0 },
	{ MOD | SHIFT, XK_f,     int_full,  0 },
	{ MOD,         XK_1,     change_ws, 0 },
	{ MOD,         XK_2,     change_ws, 1 },
	{ MOD,         XK_3,     change_ws, 2 },
	{ MOD,         XK_4,     change_ws, 3 },
	{ MOD | SHIFT, XK_1,     send_ws,   0 },
	{ MOD | SHIFT, XK_2,     send_ws,   1 },
	{ MOD | SHIFT, XK_3,     send_ws,   2 },
	{ MOD | SHIFT, XK_4,     send_ws,   3 },
};
