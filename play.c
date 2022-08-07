#include "play.h"
#include "rule.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char player = 'X';

void switch_player() {
    player = (player == 'X') ? 'O' : 'X';
}

mov get_move() {
    static char buffer[4] = {'\0', '\0', '\0', '\0'};
    static char *status;
    mov move;
    input:
        printf("%c's move: ", player);
        status = fgets(buffer, 4, stdin);
        if (status == NULL) {
            fputs("An error occured, exiting...", stderr);
            exit(EXIT_FAILURE);
        }
        if (buffer[0] == '\n') {
            puts("Please enter a valid move: [A-I][1-9]");
            goto input;
        }
        if (buffer[1] == '\n') {
            if (toupper(buffer[0]) == 'P') {
                move.type = PASS;
                return move;
            } else {
                puts("Please enter a valid move: [A-I][1-9]");
                goto input;
            }
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
    move.type = PLACE_STONE;
    move.coordinate = to_coord(buffer);
    return move;
}

void play(mov move) {
    static bool X_pass = false;
    static bool O_pass = false;
    if (move.type == PASS) {
        if (player == 'X') {
            X_pass = true;
        } else {
            O_pass = true;
        }
        if (X_pass && O_pass) {
            calculate_score();
        }
        switch_player();
        return;
    }
    if (player == 'X') {
        X_pass = false;
    } else {
        O_pass = false;
    }
    coord coordinate = move.coordinate;
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

void calculate_score() {
    fputs("Game ended!", stdout);
    exit(EXIT_SUCCESS);
}