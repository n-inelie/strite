#ifndef STAGE_H
#define STAGE_H

#include <ncurses.h>
#include "commands.h"

struct stage {
    WINDOW *window;
    size_t max_y;
    size_t max_x;
    size_t min_y;
    size_t min_x;
    size_t line_nr_width;
};

struct cursor {
    enum mode mode;
    struct stage *stage;
    size_t x;
    size_t y;
};

void render_stage(struct stage *stage, struct cursor *cursor);
void handle_input(struct cursor *cursor, int c);
void cursor_move(struct cursor *cursor, size_t y, size_t x);


#endif
