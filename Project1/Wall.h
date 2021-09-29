#pragma once
#include "Cell.h"

class Wall : public Cell {
public:

	Wall();
	Wall(Board *source, int x, int y);
};