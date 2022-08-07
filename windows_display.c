#include "board.h"
#include <stdio.h>
#include <windows.h>

typedef enum _concol {
    red = 4,
    blue = 9,
    default_color = 7
} concol;

void show_board() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < sizeof(board); i++) {
        switch (board[i]) {
            case 'X':
                SetConsoleTextAttribute(console, red);
                putchar(board[i]);
                SetConsoleTextAttribute(console, default_color);
                break;
            case 'O':
                SetConsoleTextAttribute(console, blue);
                putchar(board[i]);
                SetConsoleTextAttribute(console, default_color);
                break;
            default:
                putchar(board[i]);
        }
    }
    putchar('\n');
}