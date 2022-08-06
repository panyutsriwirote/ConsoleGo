#include "play.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char player = 'X';

void switch_player() {
    if (player == 'X') {
        player = 'O';
    } else {
        player = 'X';
    }
}

coord get_coord() {
    static char buffer[4] = {'\0', '\0', '\0', '\0'};
    static char *status;
    input:
        printf("%c's move: ", player);
        status = fgets(buffer, 4, stdin);
        if (status == NULL) {
            fputs("An error occured, exiting...", stderr);
            exit(EXIT_FAILURE);
        }
        if (buffer[0] == '\n' || buffer[1] == '\n') {
            puts("Please enter a valid move: [A-I][1-9]");
            goto input;
        }
        if (buffer[2] != '\n') {
            puts("Please enter a valid move: [A-I][1-9]");
            while (getchar() != '\n') {
                continue;
            }
            goto input;
        }
        char letter = toupper(buffer[0]);
        char num = buffer[1];
        if (letter < 'A' || letter > 'I' || num < '1' || num > '9') {
            puts("Please enter a valid move: [A-I][1-9]");
            goto input;
        }
    return to_coord(buffer);
}

void play(coord coordinate) {
    if (board[coordinate] != ' ') {
        puts("Slot already taken, please make another move");
        return;
    }
    /*******************************************************/
    /*********************GO LOGIC HERE*********************/
    /*******************************************************/
    board[coordinate] = player;
    /*******************************************************/
    /*********************GO LOGIC HERE*********************/
    /*******************************************************/
    puts(board);
    switch_player();
}