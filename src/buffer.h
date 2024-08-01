#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

struct buffer {
    size_t buffer_size;
    char *text;
    size_t index;
};

void append_buffer(struct buffer *b, char *text);

#endif
