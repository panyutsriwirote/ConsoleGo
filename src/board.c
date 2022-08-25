#include "board.h"
#include "play.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*********************************************/
/*                A 9x9 Board                */
/*********************************************/

static board init_board =
{
    .prev = NULL, .prev_move = {.type = PLACE_STONE},
    .board =
"\
    A   B   C   D   E   F   G   H   I\n\
  +---+---+---+---+---+---+---+---+---+\n\
9 |   |   |   |   |   |   |   |   |   |\n\
  +---+---+---+---+---+---+---+---+---+\n\
8 |   |   |   |   |   |   |   |   |   |\n\
  +---+---+---+---+---+---+---+---+---+\n\
7 |   |   |   |   |   |   |   |   |   |\n\
  +---+---+---+---+---+---+---+---+---+\n\
6 |   |   |   |   |   |   |   |   |   |\n\
  +---+---+---+---+---+---+---+---+---+\n\
5 |   |   |   |   |   |   |   |   |   |\n\
  +---+---+---+---+---+---+---+---+---+\n\
4 |   |   |   |   |   |   |   |   |   |\n\
  +---+---+---+---+---+---+---+---+---+\n\
3 |   |   |   |   |   |   |   |   |   |\n\
  +---+---+---+---+---+---+---+---+---+\n\
2 |   |   |   |   |   |   |   |   |   |\n\
  +---+---+---+---+---+---+---+---+---+\n\
1 |   |   |   |   |   |   |   |   |   |\n\
  +---+---+---+---+---+---+---+---+---+\
"
};

board* cur_board = &init_board;
void next_board(mov prev_move) {
    board* new_board = (board*) malloc(sizeof(board));
    new_board->prev = cur_board;
    strcpy(new_board->board, cur_board->board);
    new_board->prev_move = prev_move;
    cur_board = new_board;
}

void undo(bool undo_by_player) {
    board* prev_board = cur_board->prev;
    if (prev_board == NULL) {
        puts("Cannot go back any further!");
        return;
    }
    free(cur_board);
    cur_board = prev_board;
    if (undo_by_player) {
        switch_player;
        show_cur_board();
    }
}

/*********************************************/
/*          Edge checking functions          */
/*********************************************/

bool is_top(coord coordinate) {
    switch (coordinate) {
        case A9:
        case B9:
        case C9:
        case D9:
        case E9:
        case F9:
        case G9:
        case H9:
        case I9:
            return true;
        default:
            return false;
    }
}

bool is_bottom(coord coordinate) {
    switch (coordinate) {
        case A1:
        case B1:
        case C1:
        case D1:
        case E1:
        case F1:
        case G1:
        case H1:
        case I1:
            return true;
        default:
            return false;
    }
}

bool is_leftmost(coord coordinate) {
    switch (coordinate) {
        case A1:
        case A2:
        case A3:
        case A4:
        case A5:
        case A6:
        case A7:
        case A8:
        case A9:
            return true;
        default:
            return false;
    }
}

bool is_rightmost(coord coordinate) {
    switch (coordinate) {
        case I1:
        case I2:
        case I3:
        case I4:
        case I5:
        case I6:
        case I7:
        case I8:
        case I9:
            return true;
        default:
            return false;
    }
}