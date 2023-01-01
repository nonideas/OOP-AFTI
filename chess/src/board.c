#include <stdarg.h>
#include "board.h"
#include "chessmen/bishop.h"
#include "chessmen/king.h"
#include "chessmen/knight.h"
#include "chessmen/queen.h"
#include "chessmen/rook.h"
#include "slist.h"

#define empty_field  '_'

static void* Board_ctor(void* _self)
{
	Board* self = NULL;
	if (_self) {
		self = (Board*)_self;
        for (int i = ROW - 1; i >= 0; i--)
        {
            for (int j = 0; j < COL; j++)
            {
                self->board[i][j] = empty_field;
            }
        }
	}
    return self;
}

void print_board(void* _self)
{
    Board* self = NULL;
    if (_self) {
        self = (Board*)_self;
        printf("     ");
        for (int j = 0; j < ROW; j++)
        {
            printf("%d    ", j + 1);
        }
        printf("\n\n");
        for (int i = 0; i < ROW; i++)
        {
            printf("%d    ", i + 1);
            for (int j = 0; j < COL; j++)
            {
                printf("%c    ", self->board[i][j]);
            }
            printf("\n\n");
        }
    }
}

static void set_chessman(void* _self, int x, int y, char chessman)
{
    Board* self = NULL;
    if (_self) {
        self = (Board*)_self;
        self->board[x][y] = chessman;
    }
}

void set_chessmen(void* _board, void* chessmen)
{
    Board* board = NULL;
    if (_board) {
        board = (Board*)_board;
        Board_ctor(board);
        for (size_t cur = slist_first(chessmen); cur != slist_stop(chessmen); cur = slist_next(chessmen, cur)) {

            const struct Chessman* _chessman = *(void**)slist_current(chessmen, cur);
            if (_chessman->class == Bishop) {
                set_chessman(board, _chessman->x, _chessman->y, 'B');
            }
            if (_chessman->class == King) {
                set_chessman(board, _chessman->x, _chessman->y, 'K');
            }
            if (_chessman->class == Knight) {
                set_chessman(board, _chessman->x, _chessman->y, 'N');
            }
            if (_chessman->class == Queen) {
                set_chessman(board, _chessman->x, _chessman->y, 'Q');
            }
            if (_chessman->class == Rook) {
                set_chessman(board, _chessman->x, _chessman->y, 'R');
            }
        }
    }
}

char get_chessman(void* _self, int x, int y)
{
    Board* self = NULL;
    if (_self) {
        self = (Board*)_self;
        return self->board[x][y];
    }
    return '!';
}
