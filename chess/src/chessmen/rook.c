#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "rook.h"
#include "nobody_between.h"
#include "../board.h"

static void* rook_ctor(void* _self, va_list* app) {
    struct Rook* self = NULL;

    if (_self) {
        self = ((const struct Class*)Chessman)->ctor(_self, app);
    }
    return self;
}

static void check_rook(const void* self, const void* board) {
    const struct Chessman* _chessman = self;

    int x = _chessman->x;
    int y = _chessman->y;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            char chessman = get_chessman(board, i, j);
            if (chessman == '_' || (i == x && j == y)) {
                continue;
            }
            if (i == x || j == y) {
                if (x == i) {
                    int min_y = min(j, y);
                    int max_y = max(j, y);
                    if (nobody_in_horiz(x, min_y + 1, max_y - 1, board)) {
                        printf("R at (%d, %d) beats %c at (%d, %d) \n", x + 1, y + 1, chessman, i + 1, j + 1);
                    }
                }
                if (j == y) {
                    int min_x = min(i, x);
                    int max_x = max(i, x);
                    if (nobody_in_vert(y, min_x + 1, max_x - 1, board)) {
                        printf("R at (%d, %d) beats %c at (%d, %d) \n", x + 1, y + 1, chessman, i + 1, j + 1);
                    }
                }
            }
        }
    }
}

static const struct Class _Rook = { sizeof(struct Chessman), rook_ctor, NULL, check_rook };
const void* Rook = &_Rook;