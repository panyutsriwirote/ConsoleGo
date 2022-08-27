#include "rule.h"
#include <stdio.h>

#ifdef _WIN32

#include <windows.h>

typedef enum _col {
    red = 4,
    blue = 9,
    red_backgroud = 64,
    blue_backgroud = 144
} col;

static HANDLE console;
static CONSOLE_SCREEN_BUFFER_INFO info;
static WORD default_color;

static void display(col color, char c) {
    SetConsoleTextAttribute(console, color);
    putchar(c);
    SetConsoleTextAttribute(console, default_color);
}

void show_cur_board() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &info);
    default_color = info.wAttributes;
    for (char* c = cur_board->board; *c != '\0'; c++) {
        switch (*c) {
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
                putchar(*c);
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

#else

void show_cur_board() {
    for (char* c = cur_board->board; *c != '\0'; c++) {
        switch (*c) {
            case 'Y':
            case 'P':
                putchar(' ');
                break;
            default:
                putchar(*c);
        }
    }
    putchar('\n');
    printf("             X's prisoner: %d\n", X_prisoner);
    printf("             O's prisoner: %d\n", O_prisoner);
}

#endif