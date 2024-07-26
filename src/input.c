#include "stage.h"
#include <ncurses.h>

static size_t cursor_text_pos[2] = {0, 0};

inline void cursor_move(struct cursor *cursor, size_t y, size_t x) {
    cursor->y = y;
    cursor->x = x;
    move(y, x);
}

int handle_command_mode(struct stage *stage, struct cursor *cursor, int c) {
    (void)stage;
    addch('a');
    CURSOR_MOVE_X(cursor, 1);

    if (c == 27) {
        cursor->mode = NORMAL;
        cursor_move(cursor, cursor_text_pos[0], cursor_text_pos[1]);
    } else {
        CURSOR_MOVE_X(cursor, 1);
    }
    return CONTINUE;
}

int handle_insert_mode(struct stage *stage, struct cursor *cursor, int c) {
    (void)stage;
    // Escape
    if (c == 27) {
        cursor->mode = NORMAL;
    } else {
        CURSOR_MOVE_X(cursor, 1);
        cursor_text_pos[0] = cursor->y;
        cursor_text_pos[1] = cursor->x;
    }
    return CONTINUE;
}

int handle_normal_mode(struct stage *stage, struct cursor *cursor, int c) {
    cursor_text_pos[0] = cursor->y;
    cursor_text_pos[1] = cursor->x;
    switch (c) {
    case 'q':
        // This one is temporary
        return EXIT;
        break;
    case ':':
        cursor->mode = COMMAND;
        cursor_move(cursor, stage->max_y - 1, stage->min_x);
        handle_command_mode(stage, cursor, c);
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
        return handle_normal_mode(stage, cursor, c);
        break;
    case INSERT:
        return handle_insert_mode(stage, cursor, c);
        break;
    case COMMAND:
        return handle_command_mode(stage, cursor, c);
        break;
    case SELECT:
        // TODO
        break;
    }
    return CONTINUE;
}
