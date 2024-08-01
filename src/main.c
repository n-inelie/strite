#include "input.h"
#include "stage.h"
#include "buffer.h"
#include <ncurses.h>

int main(void) {
    initscr();
    // noecho();
    clear();

    struct buffer b = {0, "", 0};
    Stage s = {stdscr, &b, NORMAL, 0, 0, LINES, COLS};

    int input_ch;
    int output_code;

    Stage *current_stage = &s;

    do {
        render_stage(current_stage);

        input_ch = getch();
        output_code = handle_input(input_ch, &current_stage->mode);

        switch (output_code) {
        case EXIT:
            endwin();
            return 0;
            break;
        case CONTINUE:
            break;
        }

    } while (1);

    endwin();
    return 0;
}
