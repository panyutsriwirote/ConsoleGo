#ifndef RULE_H
#define RULE_H

#include "board.h"

#define explore_environment(coordinate)\
    char color = board[coordinate];\
    coord up_slot = is_top(coordinate) ? edge : up(coordinate);\
    coord down_slot = is_bottom(coordinate) ? edge : down(coordinate);\
    coord left_slot = is_leftmost(coordinate) ? edge : left(coordinate);\
    coord right_slot = is_rightmost(coordinate) ? edge : right(coordinate);

extern int X_prisoner;
extern int O_prisoner;

void remove_group(coord coordinate);
bool is_captured(coord coordinate);

#endif