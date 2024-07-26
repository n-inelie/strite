#include "stage.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    clear();

    FILE *f = fopen("sample.txt", "rb");
    if (!f) {
        return -1;
    }
    char buffer[4096];
    size_t bytes_read = fread(buffer, sizeof(char), sizeof(buffer), f);

    char **lines = malloc(sizeof(char *) * 32);
    char *line = malloc(sizeof(char) * 128);
    
    size_t line_count = 0;
    size_t line_index = 0;

    for (size_t i = 0; i < bytes_read; ++i) {
        line[line_index] = buffer[i];
        line_index++;

        if (buffer[i] == '\n') {
            lines[line_count] = line;
            line_count++;

            line = malloc(sizeof(char) * 128);
            line_index = 0;
        }

    }

    int c;
    struct page page = {lines, line_count, f, "sample.txt"};
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

    free(lines);
    endwin();
    fclose(f);
    return 0;
}
