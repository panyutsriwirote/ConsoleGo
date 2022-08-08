#include "rule.h"
#include <stdio.h>
#include <windows.h>

typedef enum {
    red = 4,
    blue = 9,
    red_backgroud = 64,
    blue_backgroud = 144
} col;

static HANDLE console;
static CONSOLE_SCREEN_BUFFER_INFO info;
static WORD default_color;

static inline void display(col color, char c) {
    SetConsoleTextAttribute(console, color);
    putchar(c);
    SetConsoleTextAttribute(console, default_color);
}

void show_board() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &info);
    default_color = info.wAttributes;
    for (int i = 0; i < sizeof(board); i++) {
        switch (board[i]) {
            case 'X':
                display(red, 'X');
                break;
            case 'O':
                display(blue, 'O');
                break;
            case 'Y':
                display(red_backgroud, ' ');
                break;
            case 'P':
                display(blue_backgroud, ' ');
                break;
            default:
                putchar(board[i]);
        }
    }
    putchar('\n');
    fputs("             ", stdout);
    display(red, 'X');
    printf("'s prisoner: %d\n", X_prisoner);
    fputs("             ", stdout);
    display(blue, 'O');
    printf("'s prisoner: %d\n", O_prisoner);
}