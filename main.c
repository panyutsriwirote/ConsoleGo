#include "play.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    show_board();
    puts("Enter a coordinate ([A-I][1-9]) to place a stone or enter P to pass");
    while (true) {
        play(get_move());
    }
    return EXIT_SUCCESS;
}