#include "rule.h"

void remove_group(coord coordinate) {
    explore_environment(coordinate)
    board[coordinate] = ' ';
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

bool group_is_surrounded(coord coordinate) {
    explore_environment(coordinate)
    if (
        board[up_slot] == ' ' ||
        board[down_slot] == ' ' ||
        board[left_slot] == ' ' ||
        board[right_slot] == ' '
    ) {
        return false;
    }
    board[coordinate] = (color == 'X') ? 'Y' : 'P';
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

void unmark_board() {
    for (int i = 0; i < sizeof(board); i++) {
        switch (board[i]) {
            case 'Y':
                board[i] = 'X';
                break;
            case 'P':
                board[i] = 'O';
                break;
        }
    }
}

bool is_captured(coord coordinate) {
    bool status = group_is_surrounded(coordinate);
    unmark_board();
    return status;
}

bool is_legal(coord coordinate) {
    return true;
}