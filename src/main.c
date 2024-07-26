#include "stage.h"
#include <ncurses.h>

int main(void) {
    initscr();
    noecho();
    clear();

    int c;
    struct stage stage = {stdscr, LINES, COLS, 0, 0, 4};
    struct cursor cursor = {NORMAL, stage.min_y,
                            stage.min_x + stage.line_nr_width};

    int code;
    do {
        render_stage(&stage, &cursor);
        c = getch();
        code = handle_input(&stage, &cursor, c);
        if (code == EXIT) {
            break;
        }
    } while (1);

    endwin();
    return 0;
}
