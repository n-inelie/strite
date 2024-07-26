#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "stage.h"

void move_down(struct stage *stage, struct cursor *cursor);
void move_up(struct stage *stage, struct cursor *cursor);
void move_left(struct stage *stage, struct cursor *cursor);
void move_right(struct stage *stage, struct cursor *cursor);

#endif
