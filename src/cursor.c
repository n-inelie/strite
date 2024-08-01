#include "cursor.h"
#include <ncurses.h>

void cursor_move(Cursor *c, size_t y, size_t x) {
    c->y = y;
    c->x = x;
    move(y, x);
}
