#include "rule.h"

int X_prisoner = 0;
int O_prisoner = 0;

void remove_group(coord coordinate) {
    char color = board[coordinate];
    explore_environment(coordinate)
    board[coordinate] = ' ';
    if (color == 'X') {
        O_prisoner++;
    } else {
        X_prisoner++;
    }
    if (board[up_slot] == color) {
        remove_group(up_slot);
    }
    if (board[down_slot] == color) {
        remove_group(down_slot);
    }
    if (board[left_slot] == color) {
        remove_group(left_slot);
    }
    if (board[right_slot] == color) {
        remove_group(right_slot);
    }
}

static bool group_is_surrounded(coord coordinate) {
    explore_environment(coordinate)
    if (
        board[up_slot] == ' ' ||
        board[down_slot] == ' ' ||
        board[left_slot] == ' ' ||
        board[right_slot] == ' '
    ) {
        return false;
    }
    char color = board[coordinate];
    board[coordinate] = (color == 'X') ? 'B' : 'W';
    if (board[up_slot] == color) {
        if (!group_is_surrounded(up_slot)) {
            return false;
        }
    }
    if (board[down_slot] == color) {
        if (!group_is_surrounded(down_slot)) {
            return false;
        }
    }
    if (board[left_slot] == color) {
        if (!group_is_surrounded(left_slot)) {
            return false;
        }
    }
    if (board[right_slot] == color) {
        if (!group_is_surrounded(right_slot)) {
            return false;
        }
    }
    return true;
}

static void unmark_board() {
    for (coord i = A9; i <= A1; i = down(i)) {
        for (
            coord coordinate = i, right_edge = i + 32;
            coordinate <= right_edge;
            coordinate += 4
        ) {
            switch (board[coordinate]) {
                case 'B':
                    board[i] = 'X';
                    break;
                case 'W':
                    board[i] = 'O';
                    break;
            }
        }
    }
}

bool is_captured(coord coordinate) {
    bool status = group_is_surrounded(coordinate);
    unmark_board();
    return status;
}