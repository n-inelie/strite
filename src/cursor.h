#ifndef CURSOR_H
#define CURSOR_H

#include <stddef.h>

typedef struct {
    size_t y;
    size_t x;
} Cursor;

void cursor_move(Cursor *c, size_t y, size_t x);

#define MOVE_X(c, delta_x) cursor_move(c, (c)->y, (c)->x + delta_x) 
#define MOVE_Y(c, delta_y) cursor_move(c, (c)->y + delta_y, (c)->x) 

#endif
