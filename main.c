#include <stdlib.h>
#include "play.h"

int main() {
    show_board();
    while (true) {
        play(get_move());
    }
    return EXIT_SUCCESS;
}