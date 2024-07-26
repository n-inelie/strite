#include "movement.h"
#include "stage.h"

static size_t cursor_text_pos[2] = {0, 0};

inline void cursor_move(struct cursor *cursor, size_t y, size_t x) {
    cursor->y = y;
    cursor->x = x;
    move(y, x);
}

int handle_command_mode(struct stage *stage, struct cursor *cursor, int c) {
    (void)stage;
    if (c == 27) {
        cursor->mode = NORMAL;
        cursor_move(cursor, cursor_text_pos[0], cursor_text_pos[1]);
    } else {
        addch(c);
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
    case KEY_DOWN:
        move_down(stage, cursor);
        break;
    case 'k':
    case KEY_UP:
        move_up(stage, cursor);
        break;
    case 'h':
    case KEY_LEFT:
        move_left(stage, cursor);
        break;
    case 'l':
    case KEY_RIGHT:
        move_right(stage, cursor);
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
