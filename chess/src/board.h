#pragma once
#include "new.h"

#define COL 8
#define ROW 8

typedef struct {
	const void *_class;
	char board[ROW][COL];
}Board;

void print_board(void* _self);
void set_chessmen(void* _board, void* chestmen);
char get_chessman(void* _self, int x, int y);
