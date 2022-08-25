#ifndef RULE_H
#define RULE_H

#include "board.h"

#define KOMI 6.5

#define explore_environment(coordinate)\
    coord up_slot = is_top(coordinate) ? EDGE : up(coordinate);\
    coord down_slot = is_bottom(coordinate) ? EDGE : down(coordinate);\
    coord left_slot = is_leftmost(coordinate) ? EDGE : left(coordinate);\
    coord right_slot = is_rightmost(coordinate) ? EDGE : right(coordinate);

extern int X_prisoner;
extern int O_prisoner;

void remove_group(coord coordinate);
bool is_captured(coord coordinate);

#endif