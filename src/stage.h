#ifndef STAGE_H
#define STAGE_H

#include <ncurses.h>
#include "commands.h"

#define CONTINUE 0
#define EXIT 1

struct page {
    char **text;
    size_t line_count;
    FILE *f;
    char *file_name;
};

struct stage {
    WINDOW *window;
    size_t max_y;
    size_t max_x;
    size_t min_y;
    size_t min_x;
    size_t line_nr_width;
    struct page *page;
};

struct cursor {
    enum mode mode;
    size_t y;
    size_t x;
};

void render_stage(struct stage *stage, struct cursor *cursor);
int handle_input(struct stage *stage, struct cursor *cursor, int c);
void cursor_move(struct cursor *cursor, size_t y, size_t x);

#define CURSOR_MOVE_X(cursor, delta_x) cursor_move(cursor, cursor->y, cursor->x + delta_x)
#define CURSOR_MOVE_Y(cursor, delta_y) cursor_move(cursor, cursor->y + delta_y, cursor->x)

#endif
