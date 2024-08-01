#include "stage.h"
#include "cursor.h"

static inline void render_status_line(Stage *s) {
    Cursor c;
    cursor_move(&c, s->max_y - 2, s->min_x + 1);

    switch(s->mode) {
    case NORMAL:
        wprintw(s->w, "NORMAL");
        break;
    case INSERT:
        wprintw(s->w, "INSERT");
        break;
    }
}

static inline void render_buffer(Stage *s) {
    Cursor c = {s->min_y, s->min_x};
    for(size_t i = 0; i < s->b->buffer_size; ++i) {
        if (s->b->text[i] == '\n'){
            MOVE_Y(&c, 1);
            continue;
        }
        addch(s->b->text[i]);
        MOVE_X(&c, 1);
    }
}

void render_stage(Stage *s) {
    wclear(s->w);
    render_status_line(s);
    render_buffer(s);
}
