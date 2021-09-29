#pragma once
#include "Cell.h"

class Plains : public Cell {
public:
	Plains();
	Plains(Board* source, int x, int y);
	void onInteract(Player* cel);
};