#pragma once

#include "board.h"
#include "slist.h"

struct Chessman* parse_data(const char* file_name);
void delete_data(struct Chessman* _slist);