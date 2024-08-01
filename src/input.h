#ifndef INPUT_H
#define INPUT_H

#define CONTINUE 0
#define EXIT 1

enum mode {
    NORMAL,
    INSERT,
};

int handle_input(int input_ch, enum mode *mode);

#endif
