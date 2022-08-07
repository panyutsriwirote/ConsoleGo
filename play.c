#include "play.h"
#include "rule.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char player = 'X';

void switch_player() {
    player = (player == 'X') ? 'O' : 'X';
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
    explore_environment(coordinate)
    if (color != ' ') {
        puts("Slot already taken, please make another move");
        return;
    }
    /*******************************************************/
    /*                       Go Logic                      */
    /*******************************************************/
    board[coordinate] = player;
    char enemy = (player == 'X') ? 'O' : 'X';
    if (board[up_slot] == enemy) {
        if (is_captured(up_slot)) {
            remove_group(up_slot);
        }
    }
    if (board[down_slot] == enemy) {
        if (is_captured(down_slot)) {
            remove_group(down_slot);
        }
    }
    if (board[left_slot] == enemy) {
        if (is_captured(left_slot)) {
            remove_group(left_slot);
        }
    }
    if (board[right_slot] == enemy) {
        if (is_captured(right_slot)) {
            remove_group(right_slot);
        }
    }
    if (is_captured(coordinate)) {
        remove_group(coordinate);
    }
    /*******************************************************/
    /*                       Go Logic                      */
    /*******************************************************/
    show_board();
    switch_player();
}