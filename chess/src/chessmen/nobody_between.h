#pragma once
#include <stdbool.h>
#include "../board.h"

enum diag_type
{
	diag_topLeft_downRignt,
	diag_downLeft_topRight
};

bool nobody_in_horiz(int line, int y1, int y2, const void* board);
bool nobody_in_vert(int row, int x1, int x2, const void* board);
bool nobody_in_diag(int x1, int y1, int x2, int y2, enum diag_type type_diag, const void* board);