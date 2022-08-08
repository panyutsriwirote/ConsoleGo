#include "play.h"
#include "rule.h"
#include <stdio.h>
#include <stdlib.h>

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
            puts("Please enter a valid move: [A-I][1-9] or P to pass");
            goto input;
        }
        if (buffer[1] == '\n') {
            if (toupper(buffer[0]) == 'P') {
                move.type = PASS;
                return move;
            } else {
                puts("Please enter a valid move: [A-I][1-9] or P to pass");
                goto input;
            }
        }
        if (buffer[2] != '\n') {
            puts("Please enter a valid move: [A-I][1-9] or P to pass");
            while (getchar() != '\n') {
                continue;
            }
            goto input;
        }
        char letter = toupper(buffer[0]);
        char num = buffer[1];
        if (letter < 'A' || letter > 'I' || num < '1' || num > '9') {
            puts("Please enter a valid move: [A-I][1-9] or P to pass");
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
    char color = board[coordinate];
    if (color != ' ') {
        puts("Slot already taken, please make another move");
        return;
    }
    /*******************************************************/
    /*                       Go Logic                      */
    /*******************************************************/
    board[coordinate] = player;
    char enemy = (player == 'X') ? 'O' : 'X';
    explore_environment(coordinate)
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

static bool surrounded_by_X = false;
static bool surrounded_by_O = false;

static void transverse_territory(coord coordinate);
static inline void check_surrounding(coord coordinate) {
    switch (board[coordinate]) {
        case 'X':
            surrounded_by_X = true;
            break;
        case 'O':
            surrounded_by_O = true;
            break;
        case ' ':
            transverse_territory(coordinate);
            break;
    }
}

static void transverse_territory(coord coordinate) {
    board[coordinate] = 'V';
    explore_environment(coordinate)
    check_surrounding(up_slot);
    check_surrounding(down_slot);
    check_surrounding(left_slot);
    check_surrounding(right_slot);
}

static char territory_owner(coord coordinate) {
    transverse_territory(coordinate);
    char owner;
    if (surrounded_by_X && !surrounded_by_O) {
        owner = 'B';
    } else if (surrounded_by_O && !surrounded_by_X) {
        owner = 'W';
    } else {
        owner = ' ';
    }
    surrounded_by_X = surrounded_by_O = false;
    return owner;
}

static void paint_territory(coord coordinate) {
    char paint = territory_owner(coordinate);
    for (coord i = A9; i <= A1; i = down(i)) {
        for (
            coord coordinate = i, right_edge = i + 32;
            coordinate <= right_edge;
            coordinate = right(coordinate)
        ) {
            if (board[coordinate] == 'V') {
                board[coordinate] = paint;
            }
        }
    }
}

static int X_territory = 0;
static int O_territory = 0;
static void count_territory() {
    for (coord i = A9; i <= A1; i = down(i)) {
        for (
            coord coordinate = i, right_edge = i + 32;
            coordinate <= right_edge;
            coordinate += 4
        ) {
            switch (board[coordinate]) {
                case 'B':
                    X_territory++;
                    break;
                case 'W':
                    O_territory++;
                    break;
            }
        }
    }
}

static mov get_dead_stone() {
    static char buffer[4] = {'\0', '\0', '\0', '\0'};
    static char *status;
    mov move;
    input:
        fputs("Select dead group: ", stdout);
        status = fgets(buffer, 4, stdin);
        if (status == NULL) {
            fputs("An error occured, exiting...", stderr);
            exit(EXIT_FAILURE);
        }
        if (buffer[0] == '\n') {
            puts("Please enter a valid location: [A-I][1-9] or P to finish");
            goto input;
        }
        if (buffer[1] == '\n') {
            if (toupper(buffer[0]) == 'P') {
                move.type = PASS;
                return move;
            } else {
                puts("Please enter a valid location: [A-I][1-9] or P to finish");
                goto input;
            }
        }
        if (buffer[2] != '\n') {
            puts("Please enter a valid location: [A-I][1-9] or P to finish");
            while (getchar() != '\n') {
                continue;
            }
            goto input;
        }
        char letter = toupper(buffer[0]);
        char num = buffer[1];
        if (letter < 'A' || letter > 'I' || num < '1' || num > '9') {
            puts("Please enter a valid location: [A-I][1-9] or P to finish");
            goto input;
        }
    move.type = PLACE_STONE;
    move.coordinate = to_coord(buffer);
    return move;
}

static void remove_dead_group() {
    start:
    mov input = get_dead_stone();
    if (input.type == PASS) {
        return;
    }
    coord coordinate = input.coordinate;
    if (board[coordinate] == ' ') {
        puts("There is no stone at the specified location");
        goto start;
    }
    remove_group(coordinate);
    show_board();
    goto start;
}

void calculate_score() {
    puts("Game Over!");
    puts("Select dead groups to remove, enter P when finished");
    remove_dead_group();
    for (coord i = A9; i <= A1; i = down(i)) {
        for (
            coord coordinate = i, right_edge = i + 32;
            coordinate <= right_edge;
            coordinate = right(coordinate)
        ) {
            if (board[coordinate] == ' ') {
                paint_territory(coordinate);
            }
        }
    }
    count_territory();
    int X_score = X_territory + X_prisoner;
    float O_score = O_territory + O_prisoner + KOMI;
    printf("X's score: %d\n", X_score);
    printf("O's score: %.1f\n", O_score);
    if (X_score > O_score) {
        printf("X wins by %.1f point", X_score - O_score);
    } else {
        printf("O wins by %.1f point", O_score - X_score);
    }
    exit(EXIT_SUCCESS);
}