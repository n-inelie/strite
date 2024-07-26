#include "stage.h"
#include <ncurses.h>

inline void cursor_move(struct cursor *cursor, size_t y, size_t x) {
    cursor->y = y;
    cursor->x = x;
    move(y, x);
}

int handle_input_insert_mode(struct stage *stage, struct cursor *cursor, int c) {
    (void)stage;
    // Escape
    if (c == 27) {
        cursor->mode = NORMAL;
    } else {
        cursor_move(cursor, cursor->y, cursor->x + 1);
    }
    return CONTINUE;
}

int handle_input_normal_mode(struct stage *stage, struct cursor *cursor,
                              int c) {
    switch (c) {
    case 'q':
        // This one is temporary
        return EXIT;
        break;
    case ':':
        cursor->mode = COMMAND;
        cursor_move(cursor, stage->max_y, stage->min_x);
        break;
    case 'i':
        cursor->mode = INSERT;
        break;
    case 'j':
        if (cursor->y < stage->max_y - 3) {
            cursor_move(cursor, cursor->y + 1, cursor->x);
        }
        break;
    case 'k':
        if (cursor->y != 0) {
            cursor_move(cursor, cursor->y - 1, cursor->x);
        }
        break;
    case 'h':
        if (cursor->x > stage->min_x + stage->line_nr_width + 1) {
            cursor_move(cursor, cursor->y, cursor->x - 1);
        }
        break;
    case 'l':
        if (cursor->x < stage->max_x) {
            cursor_move(cursor, cursor->y, cursor->x + 1);
        }
        break;
    }
    return CONTINUE;
}

int handle_input(struct stage *stage, struct cursor *cursor, int c) {
    switch (cursor->mode) {
    case NORMAL:
        return handle_input_normal_mode(stage, cursor, c);
        break;
    case INSERT:
        return handle_input_insert_mode(stage, cursor, c);
        break;
    case COMMAND:
        // TODO
        break;
    case SELECT:
        // TODO
        break;
    }
    return CONTINUE;
}
