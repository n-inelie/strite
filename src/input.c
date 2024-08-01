#include "input.h"

static inline int handle_insert(int input_ch, enum mode *mode) {
    switch(input_ch) {
        case 27:
            *mode = NORMAL;
            break;
    }
    return CONTINUE;
}

static inline int handle_normal(int input_ch, enum mode *mode) {
    switch (input_ch) {
    case 'q':
        return EXIT;
        break;
    case 'i':
        *mode = INSERT;
        break;
    }
    return CONTINUE;
}

int handle_input(int input_ch, enum mode *mode) {
    switch (*mode) {
    case NORMAL:
        return handle_normal(input_ch, mode);
        break;
    case INSERT:
        return handle_insert(input_ch, mode);
        break;
    }
}
