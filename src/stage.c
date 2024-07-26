#include "stage.h"

static inline void render_line_nr(struct stage *stage) {
    // TODO
    (void)stage;
}

static inline void render_status_bar(struct stage *stage,
                                     struct cursor *cursor) {
    struct cursor temp_cursor = *cursor;
    cursor_move(cursor, stage->max_y - 2, stage->min_x + 1);
    switch (cursor->mode) {
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
    CURSOR_MOVE_X(cursor, 8);
    mvprintw(cursor->y, cursor->x, "%s", stage->page->file_name);
    cursor_move(cursor, temp_cursor.y, temp_cursor.x);
}

static inline void render_text(struct stage *stage, struct cursor *cursor) {
    struct cursor temp_cursor = *cursor;
    cursor_move(cursor, 0, stage->min_x + stage->line_nr_width);

    char **text = stage->page->text;
    size_t line_count = stage->page->line_count;

    for (size_t i = 0; i < line_count; ++i) {
        char *line = text[i];
        for (size_t j = 0;; ++j) {
            CURSOR_MOVE_X(cursor, 1);
            if (line[j] == '\n') {
                CURSOR_MOVE_X(cursor, -j-1);
                break;
            }
            addch(line[j]);
        }
        CURSOR_MOVE_Y(cursor, 1);
    }

    cursor_move(cursor, temp_cursor.y, temp_cursor.x);
}

void render_stage(struct stage *stage, struct cursor *cursor) {
    render_status_bar(stage, cursor);
    render_text(stage, cursor);
    render_line_nr(stage);
}
