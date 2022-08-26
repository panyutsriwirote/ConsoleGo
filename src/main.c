#include "play.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    show_cur_board();
    puts("Enter:");
    puts("   (1) a coordinate ([A-I][1-9]) to place a stone");
    puts("   (2) P to pass");
    puts("   (3) U to undo last move");
    while (true) {play(get_move());}
    return EXIT_SUCCESS;
}