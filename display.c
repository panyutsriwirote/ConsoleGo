#include "rule.h"
#include <stdio.h>

void show_board() {
    for (int i = 0; i < sizeof(board); i++) {
        switch (board[i]) {
            case 'Y':
            case 'P':
                putchar(' ');
                break;
            default:
                putchar(board[i]);
        }
    }
    putchar('\n');
    printf("             X's prisoner: %d\n", X_prisoner);
    printf("             O's prisoner: %d\n", O_prisoner);
}