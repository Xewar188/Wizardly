#pragma once
#include "Cell.h"

class UsedShrine : public Cell {
public:

	UsedShrine();
	UsedShrine(Board* source, int x, int y);
};