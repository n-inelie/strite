#include "stage.h"
#include <ncurses.h>
#include <stdio.h>

int main(void) {
    initscr();
    noecho();
    clear();

    FILE *f = fopen("sample.txt", "rb");
    if (!f) {
        return -1;
    }
    char buffer[1024];
    int bytes_read = fread(buffer, sizeof(char), sizeof(buffer), f);

    int c;
    struct page page = {buffer, bytes_read, f, "sample.txt"};
    struct stage stage = {stdscr, LINES, COLS, 0, 0, 4, &page};
    struct cursor cursor = {NORMAL, stage.min_y,
                            stage.min_x + stage.line_nr_width};

    int code;
    do {
        // clear();
        render_stage(&stage, &cursor);
        c = getch();
        code = handle_input(&stage, &cursor, c);
        if (code == EXIT) {
            break;
        }
    } while (1);

    endwin();
    fclose(f);
    return 0;
}
