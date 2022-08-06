#ifndef PLAY_H
#define PLAY_H

#include "board.h"

extern char player;
void switch_player();
coord get_coord();
void play(coord coordinate);

#endif