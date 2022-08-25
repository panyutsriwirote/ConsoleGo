#include "rule.h"

int X_prisoner = 0;
int O_prisoner = 0;

void remove_group(coord coordinate) {
    char color = slot(coordinate);
    slot(coordinate) = ' ';
    if (color == 'X')
        {O_prisoner++;}
    else
        {X_prisoner++;}
    explore_environment(coordinate)
    if (slot(up_slot) == color) {remove_group(up_slot);}
    if (slot(down_slot) == color) {remove_group(down_slot);}
    if (slot(left_slot) == color) {remove_group(left_slot);}
    if (slot(right_slot) == color) {remove_group(right_slot);}
}

static bool group_is_surrounded(coord coordinate) {
    explore_environment(coordinate)
    if (
        slot(up_slot) == ' ' ||
        slot(down_slot) == ' ' ||
        slot(left_slot) == ' ' ||
        slot(right_slot) == ' '
    ) {return false;}
    char color = slot(coordinate);
    slot(coordinate) = (color == 'X') ? 'Y' : 'P';
    if (slot(up_slot) == color){
        if (!group_is_surrounded(up_slot)) {return false;}
    }
    if (slot(down_slot) == color) {
        if (!group_is_surrounded(down_slot)) {return false;}
    }
    if (slot(left_slot) == color) {
        if (!group_is_surrounded(left_slot)) {return false;}
    }
    if (slot(right_slot) == color) {
        if (!group_is_surrounded(right_slot)) {return false;}
    }
    return true;
}

static void unmark_board() {
    for (every_row) {
        for (every_column) {
            switch (slot(coordinate)) {
                case 'Y':
                    slot(coordinate) = 'X';
                    break;
                case 'P':
                    slot(coordinate) = 'O';
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