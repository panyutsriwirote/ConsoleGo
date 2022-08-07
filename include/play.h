#ifndef PLAY_H
#define PLAY_H

#include "board.h"

typedef struct {
    enum {PASS, PLACE_STONE} type;
    coord coordinate;
} mov;

extern char player;
void switch_player();
mov get_move();
void play(mov move);
void calculate_score();

#endif