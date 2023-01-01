#include "nobody_between.h"

#define empty_field  '_'

bool nobody_in_horiz(int line, int y1, int y2, const void* board) {
    for (; y1 < y2; y1++) {
        if (get_chessman(board, line, y1) != empty_field) {
            return false;
        }
    }
    return true;
}

bool nobody_in_vert(int row, int x1, int x2, const void* board) {
    for (; x1 < x2; x1++) {
        if (get_chessman(board, x1, row) != empty_field) {
            return false;
        }
    }
    return true;
}

bool nobody_in_diag(int x1, int y1, int x2, int y2, enum diag_type type_diag, const void* board) {
    for (int i = x1, j = y1; i <= x2; i++, (type_diag == diag_topLeft_downRignt) ? j++ : j--) {
        if (get_chessman(board, i, j) != empty_field) {
            return false;
        }
    }
    return true;
}