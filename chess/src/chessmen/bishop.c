#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "bishop.h"
#include "nobody_between.h"
#include "../board.h"

#define empty_field  '_'

static void* bishop_ctor(void* _self, va_list* app) {
    struct Bishop* self = NULL;

    if (_self) {
        self = ((const struct Class*)Chessman)->ctor(_self, app);
    }
    return self;
}

static void check_bishop(const void* self, const void* board) {
    const struct Chessman* _chessman = self;
    int x = _chessman->x;
    int y = _chessman->y;

    int c1 = x - y;
    int c2 = x + y;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            char chessman = get_chessman(board, i, j);
            if (chessman == empty_field || (i == x && j == y)) {
                continue;
            }
            
            if ((i - j == c1) || (i + j) == c2) {
                if ((i - j) == c1) {
                    int min_x = min(i, x);
                    int min_y = min(j, y);
                    int max_x = max(i, x);
                    int max_y = max(j, y);
                    if (nobody_in_diag(min_x + 1, min_y + 1, max_x - 1, max_y - 1, diag_downLeft_topRight, board)) {
                        printf("B at (%d, %d) beats %c at (%d, %d) \n", x + 1, y + 1, chessman, i + 1, j + 1);
                    }
                }
                if ((i + j) == c2) {
                    int min_x = min(i, x);
                    int min_y = min(j, y);
                    int max_x = max(i, x);
                    int max_y = max(j, y);
                    if (nobody_in_diag(min_x + 1, max_y - 1, max_x - 1, min_y + 1, diag_topLeft_downRignt, board)) {
                        printf("B at (%d, %d) beats %c at (%d, %d) \n", x + 1, y + 1, chessman, i + 1, j + 1);
                    }
                }
            }

        }
    }
}

static const struct Class _Bishop = { sizeof(struct Chessman), bishop_ctor, NULL, check_bishop };
const void* Bishop = &_Bishop;