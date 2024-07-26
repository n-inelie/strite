#include "stage.h"
#include <ncurses.h>
#include <stdlib.h>

inline void cursor_move(struct cursor *cursor, size_t y, size_t x) {
    cursor->y = y;
    cursor->x = x;
    move(y + cursor->stage->min_y,
         x + cursor->stage->min_x);
}

void handle_input_insert_mode(struct cursor *cursor, int c) {
    // Escape
    if (c == 27) {
        cursor->mode = NORMAL;
    } else {
        addch(c);
        cursor_move(cursor, cursor->y, cursor->x + 1);
    }
}

void handle_input_normal_mode(struct cursor *cursor, int c) {
    switch (c) {
    case 'q':
        // This one is temporary
        clear();
        exit(EXIT_SUCCESS);
        break;
    case ':':
        cursor->mode = COMMAND;
        cursor_move(cursor, cursor->stage->max_y, cursor->stage->min_x);
        break;
    case 'i':
        cursor->mode = INSERT;
        break;
    case 'j':
        if (cursor->y < cursor->stage->max_y - 2) {
            cursor_move(cursor, cursor->y + 1, cursor->x);
        }
        cursor_move(cursor, cursor->y + 1, cursor->x);
        break;
    case 'k':
        if (cursor->y != 0) {
            cursor_move(cursor, cursor->y - 1, cursor->x);
        }
        break;
    case 'h':
        if (cursor->x > cursor->stage->min_x + cursor->stage->line_nr_width) {
            cursor_move(cursor, cursor->y, cursor->x - 1);
        }
        break;
    case 'l':
        if (cursor->x < cursor->stage->max_x) {
            cursor_move(cursor, cursor->y, cursor->x + 1);
        }
        break;
    }
}

void handle_input(struct cursor *cursor, int c) {
    switch (cursor->mode) {
    case NORMAL:
        handle_input_normal_mode(cursor, c);
        break;
    case INSERT:
        handle_input_insert_mode(cursor, c);
        break;
    case COMMAND:
        // TODO
        break;
    case SELECT:
        // TODO
        break;
    }
}
