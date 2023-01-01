#pragma once
#include "new.h"

struct Chessman {
	const void* class;
	int x;
	int y;
};

extern const void* Chessman;