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

    char *text = stage->page->text;

    size_t y_offset = 0;
    size_t x_offset = 0;
    size_t index = 0;
    while (index < stage->page->text_len) {
        cursor_move(cursor, stage->min_y + y_offset,
                    stage->min_x + stage->line_nr_width + x_offset);
        x_offset++;
        if (text[index] == '\n') {
            y_offset++;
            x_offset = 0;
        }
        addch(text[index]);
        index++;
    }

    cursor_move(cursor, temp_cursor.y, temp_cursor.x);
}

void render_stage(struct stage *stage, struct cursor *cursor) {
    render_status_bar(stage, cursor);
    render_text(stage, cursor);
    render_line_nr(stage);
}
