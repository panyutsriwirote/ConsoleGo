#include "play.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    show_cur_board();
    puts("Enter:\n   (1) a coordinate ([A-I][1-9]) to place a stone\n   (2) P to pass\n   (3) U to undo last move");
    while (true) {play(get_move());}
    return EXIT_SUCCESS;
}