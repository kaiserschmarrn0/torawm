#ifndef WINDOW_H
#define WINDOW_H

#include <xcb/xcb_icccm.h>

#include "config.h"

#define GEOM_X 0
#define GEOM_Y 1
#define GEOM_W 2
#define GEOM_H 3

#define MOVE_MASK XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y
#define RESIZE_MASK XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT
#define MOVE_RESIZE_MASK MOVE_MASK | RESIZE_MASK

enum { TYPE_ALL, TYPE_NORMAL, TYPE_ABOVE, TYPE_COUNT };

enum { WIN_CHILD, WIN_PARENT, WIN_COUNT };
#define REGION_COUNT WIN_COUNT + LEN(controls)

typedef struct window {
	struct window *next[NUM_WS][TYPE_COUNT];
	struct window *prev[NUM_WS][TYPE_COUNT];

	int normal;
	int above;
	int sticky;

	xcb_window_t windows[WIN_COUNT + LEN(controls)];
	int last_pm[LEN(controls)];

	xcb_window_t resize_regions[8];

	xcb_gcontext_t gc;

	uint32_t geom[4];

	xcb_size_hints_t hints;

	uint32_t before_roll;
	int is_roll;

	uint32_t before_snap[4];
	int snap_index;
	
	uint32_t before_full[4];	
	int is_i_full;
	int is_e_full;

	int ignore_unmap;
} window;

void release_events(window *subj);
void normal_events(window *subj);
void reset_events(window *subj);

void center_pointer(window *win);

void stack_above_helper(xcb_window_t win);
void stack_above(window *subj);
void stack_above_abnormal(window *win);

void stack_below(window *win);
void stack_below_abnormal(window *win);

void mywm_raise(window *subj);
void mywm_lower(window *win);
void safe_raise(window *subj);

void focus(window *subj);
void unfocus(window *win);

void show_state(window *win);
void show(window *win);
void hide(window *win);

void ewmh_state(window *win);

void stick_helper(window *win);

void save_state(window *win, uint32_t *state);

void full_save_state(window *win);
void full_restore_state(window *win);
void full(window *win);
void ext_full(window *win);

void free_client(window *subj, int ws);
void forget_client(window *subj, int ws);

int search_resize_regions(window *win, xcb_window_t id);

void update_geometry(window *win, uint32_t mask, const uint32_t *true_vals);

void draw_region(window *win, int window_index, int pm_index);

void cursor_clean(void);
void cursor_init(void);

extern xcb_cursor_t resize_cursors[8];

void create_window_new(xcb_window_t child);
void create_window_existing(xcb_window_t child);

#endif
