#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "king.h"
#include "nobody_between.h"
#include "../board.h"

#define empty_field  '_'

static void* king_ctor(void* _self, va_list* app) {
    struct King* self = NULL;

    if (_self) {
        self = ((const struct Class*)Chessman)->ctor(_self, app);
    }
    return self;
}

static void check_king(const void* self, const void* board) {
    const struct Chessman* _chessman = self;

    int x = _chessman->x;
    int y = _chessman->y;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            char chessman = get_chessman(board, i, j);
            if (chessman == empty_field || (i == x && j == y)) {
                continue;
            }
            if (abs(x - i) <= 1 && abs(y - j) <= 1) {
                printf("K at (%d, %d) beats %c at (%d, %d) \n", x + 1, y + 1, chessman, i + 1, j + 1);
            }
        }
    }
}

const struct Class _King = { sizeof(struct Chessman), king_ctor, NULL, check_king };
const void* King = &_King;