#include "play.h"
#include "rule.h"
#include <stdio.h>
#include <stdlib.h>

char player = 'X';

#define clear_stdin while (getchar() != '\n') continue

mov get_move() {
    static char buffer[4] = {'\0', '\0', '\0', '\0'};
    mov move;
    while (true) {
        printf("%c's move: ", player);
        char* status = fgets(buffer, 4, stdin);
        if (status == NULL) {
            fputs("An error occured, exiting...", stderr);
            exit(EXIT_FAILURE);
        }
        if (buffer[0] == '\n') {
            puts("Please enter a valid move: [A-I][1-9], P to pass, or U to undo");
            continue;
        }
        if (buffer[1] == '\n') {
            switch (toupper(buffer[0])) {
                case 'P':
                    move.type = PASS;
                    return move;
                case 'U':
                    move.type = UNDO;
                    return move;
                default:
                    puts("Please enter a valid move: [A-I][1-9], P to pass, or U to undo");
                    continue;
            }
            if (toupper(buffer[0]) == 'P') {
                move.type = PASS;
                return move;
            } else {
                puts("Please enter a valid move: [A-I][1-9], P to pass, or U to undo");
                continue;
            }
        }
        if (buffer[2] != '\n') {
            puts("Please enter a valid move: [A-I][1-9], P to pass, or U to undo");
            clear_stdin;
            continue;
        }
        char letter = toupper(buffer[0]);
        char num = buffer[1];
        if (letter < 'A' || letter > 'I' || num < '1' || num > '9') {
            puts("Please enter a valid move: [A-I][1-9], P to pass, or U to undo");
            continue;
        }
        move.type = PLACE_STONE;
        move.coordinate = to_coord(buffer);
        return move;
    }
}

static void calculate_score();
void play(mov move) {
    if (move.type == UNDO)
        {undo(true); return;}
    else if (move.type == PASS) {
        if (last_move.type == PASS) {calculate_score();}
        next_board(move);
        switch_player;
        return;
    }
    coord coordinate = move.coordinate;
    char color = slot(coordinate);
    if (color != ' ') {
        puts("Slot already taken, please make another move");
        return;
    }
    next_board(move);
    /*******************************************************/
    /*                       Go Logic                      */
    /*******************************************************/
    slot(coordinate) = player;
    char enemy = (player == 'X') ? 'O' : 'X';
    explore_environment(coordinate)
    if (slot(up_slot) == enemy) {
        if (is_captured(up_slot)) {remove_group(up_slot);}
    }
    if (slot(down_slot) == enemy) {
        if (is_captured(down_slot)) {remove_group(down_slot);}
    }
    if (slot(left_slot) == enemy) {
        if (is_captured(left_slot)) {remove_group(left_slot);}
    }
    if (slot(right_slot) == enemy) {
        if (is_captured(right_slot)) {remove_group(right_slot);}
    }
    // Suicide
    if (is_captured(coordinate)) {
        puts("Illegal move, please make another move");
        undo(false);
        return;
    }
    /*******************************************************/
    /*                       Go Logic                      */
    /*******************************************************/
    show_cur_board();
    switch_player;
}

static bool surrounded_by_X = false;
static bool surrounded_by_O = false;

static void transverse_territory(coord coordinate);
static inline void check_surrounding(coord coordinate) {
    switch (slot(coordinate)) {
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
    slot(coordinate) = 'V';
    explore_environment(coordinate)
    check_surrounding(up_slot);
    check_surrounding(down_slot);
    check_surrounding(left_slot);
    check_surrounding(right_slot);
}

static char territory_owner(coord coordinate) {
    transverse_territory(coordinate);
    char owner;
    if (surrounded_by_X && !surrounded_by_O)
        {owner = 'Y';}
    else if (surrounded_by_O && !surrounded_by_X)
        {owner = 'P';}
    else
        {owner = ' ';}
    surrounded_by_X = surrounded_by_O = false;
    return owner;
}

static void paint_territory(coord coordinate) {
    char paint = territory_owner(coordinate);
    for (every_row) {
        for (every_column) {
            if (slot(coordinate) == 'V')
                {slot(coordinate) = paint;}
        }
    }
}

static int X_territory = 0;
static int O_territory = 0;
static void count_territory() {
    for (every_row) {
        for (every_column) {
            switch (slot(coordinate)) {
                case 'Y':
                    X_territory++;
                    break;
                case 'P':
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
    while (true) {
        fputs("Select dead group: ", stdout);
        status = fgets(buffer, 4, stdin);
        if (status == NULL) {
            fputs("An error occured, exiting...", stderr);
            exit(EXIT_FAILURE);
        }
        if (buffer[0] == '\n') {
            puts("Please enter a valid location: [A-I][1-9] or P to finish");
            continue;
        }
        if (buffer[1] == '\n') {
            if (toupper(buffer[0]) == 'P') {
                move.type = PASS;
                return move;
            } else {
                puts("Please enter a valid location: [A-I][1-9] or P to finish");
                continue;
            }
        }
        if (buffer[2] != '\n') {
            puts("Please enter a valid location: [A-I][1-9] or P to finish");
            clear_stdin;
            continue;
        }
        char letter = toupper(buffer[0]);
        char num = buffer[1];
        if (letter < 'A' || letter > 'I' || num < '1' || num > '9') {
            puts("Please enter a valid location: [A-I][1-9] or P to finish");
            continue;
        }
        move.type = PLACE_STONE;
        move.coordinate = to_coord(buffer);
        return move;
    }
}

static void remove_dead_group() {
    while (true) {
        mov input = get_dead_stone();
        if (input.type == PASS) {return;}
        coord coordinate = input.coordinate;
        if (slot(coordinate) == ' ') {
            puts("There is no stone at the specified location");
            continue;
        }
        remove_group(coordinate);
        show_cur_board();
    }
}

static void calculate_score() {
    puts("Game Over!");
    puts("Select dead groups to remove, enter P when finished");
    remove_dead_group();
    for (every_row) {
        for (every_column) {
            if (slot(coordinate) == ' ')
                {paint_territory(coordinate);}
        }
    }
    show_cur_board();
    count_territory();
    int X_score = X_territory + X_prisoner;
    float O_score = O_territory + O_prisoner + KOMI;
    printf("X's score: %d\n", X_score);
    printf("O's score: %.1f\n", O_score);
    if (X_score > O_score)
        {printf("X wins by %.1f point\n", X_score - O_score);}
    else
        {printf("O wins by %.1f point\n", O_score - X_score);}
    exit(EXIT_SUCCESS);
}