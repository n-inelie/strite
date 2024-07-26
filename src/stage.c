#include "stage.h"

void render_line_nr(struct stage *stage) {
    // TODO
    (void) stage;
}

void render_status_bar(struct stage *stage, struct cursor *cursor) {
    cursor_move(cursor, stage->max_y - 1, stage->min_x + 1);
    switch(cursor->mode) {
        case NORMAL:
            mvprintw(cursor->y, cursor->x, "NORMAL");
            break;
        case INSERT:
            mvprintw(cursor->y, cursor->x, "INSERT");
            break;
        case SELECT:
            mvprintw(cursor->y, cursor->x, "SELECT");
            break;
        case COMMAND:
            mvprintw(cursor->y, cursor->x, "COMMAND");
            break;
    }
}

void render_stage(struct stage *stage, struct cursor *cursor) {
    render_status_bar(stage, cursor);
    render_line_nr(stage);
    cursor_move(cursor, stage->min_y, stage->min_x + stage->line_nr_width);
}

