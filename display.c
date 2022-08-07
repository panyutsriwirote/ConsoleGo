#include "rule.h"
#include <stdio.h>

void show_board() {
    puts(board);
    printf("             X's prisoner: %d\n", X_prisoner);
    printf("             O's prisoner: %d\n", O_prisoner);
}