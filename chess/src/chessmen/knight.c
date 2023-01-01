#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "knight.h"
#include "nobody_between.h"
#include "../board.h"

#define empty_field  '_'

static void* knight_ctor(void* _self, va_list* app) {
    struct Knight* self = NULL;

    if (_self) {
        self = ((const struct Class*)Chessman)->ctor(_self, app);
    }
    return self;
}

static void check_knight(const void* self, const void* board) {
    const struct Chessman* _chessman = self;

    int x = _chessman->x;
    int y = _chessman->y;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            char chessman = get_chessman(board, i, j);
            if (chessman == empty_field || (i == x && j == y)) {
                continue;
            }
            int deltaX = abs(x - i);
            int deltaY = abs(y - j);
            if ((deltaX == 2 && deltaY == 1) || (deltaX == 1 && deltaY == 2)) {
                printf("N at (%d, %d) beats %c at (%d, %d) \n", x + 1, y + 1, chessman, i + 1, j + 1);
            }
        }
    }
}

static const struct Class _Knight = { sizeof(struct Chessman), knight_ctor, NULL, check_knight };
const void* Knight = &_Knight;