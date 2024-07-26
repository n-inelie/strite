#include "movement.h"

inline void move_down(struct stage *stage, struct cursor *cursor) {
    if (cursor->y < stage->max_y - 3) {
        cursor_move(cursor, cursor->y + 1, cursor->x);
    }
}

inline void move_up(struct stage *stage, struct cursor *cursor) {
    (void)stage;
    if (cursor->y != 0) {
        cursor_move(cursor, cursor->y - 1, cursor->x);
    }
}

inline void move_left(struct stage *stage, struct cursor *cursor) {
    if (cursor->x > stage->min_x + stage->line_nr_width) {
        cursor_move(cursor, cursor->y, cursor->x - 1);
    }
}

inline void move_right(struct stage *stage, struct cursor *cursor) {
    if (cursor->x < stage->max_x - 1) {
        cursor_move(cursor, cursor->y, cursor->x + 1);
    }
}
