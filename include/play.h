#ifndef PLAY_H
#define PLAY_H

#include "board.h"

typedef enum _mtype {
    PASS, PLACE_STONE
} mtype;

typedef struct _mov {
    mtype type;
    coord coordinate;
} mov;

extern char player;
void switch_player();
mov get_move();
void play(mov move);
void calculate_score();

#endif