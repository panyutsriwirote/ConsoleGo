#include <stdio.h>
#include <stdlib.h>
#include "play.h"

int main() {
    show_board();
    while (true) {
        play(get_coord());
    }
    return EXIT_SUCCESS;
}