#include "rule.h"
#include <stdio.h>
#include <windows.h>

#define red 4
#define blue 9
#define default_color 7

static HANDLE console;

static inline void print_X() {
    SetConsoleTextAttribute(console, red);
    putchar('X');
    SetConsoleTextAttribute(console, default_color);
}
static inline void print_O() {
    SetConsoleTextAttribute(console, blue);
    putchar('O');
    SetConsoleTextAttribute(console, default_color);
}

void show_board() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < sizeof(board); i++) {
        switch (board[i]) {
            case 'X':
                print_X();
                break;
            case 'O':
                print_O();
                break;
            default:
                putchar(board[i]);
        }
    }
    putchar('\n');
    fputs("             ", stdout);
    print_X();
    printf("'s prisoner: %d\n", X_prisoner);
    fputs("             ", stdout);
    print_O();
    printf("'s prisoner: %d\n", O_prisoner);
}