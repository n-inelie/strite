#ifndef STAGE_H
#define STAGE_H

#include <stddef.h>
#include <ncurses.h>
#include "input.h"
#include "buffer.h"

typedef struct {
    WINDOW *w;
    struct buffer *b;
    enum mode mode;
    size_t min_y;
    size_t min_x;
    size_t max_y;
    size_t max_x;
} Stage;

void render_stage(Stage *s);

#endif
