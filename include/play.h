#ifndef PLAY_H
#define PLAY_H

#include "board.h"

extern char player;
#define switch_player player = (player == 'X') ? 'O' : 'X'

mov get_move();
void play(mov move);

#endif