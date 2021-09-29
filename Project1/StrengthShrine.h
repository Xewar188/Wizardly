#pragma once
#include "Cell.h"

class StrengthShrine : public Cell {
public:

	StrengthShrine();
	StrengthShrine(Board* source, int x, int y);
	void onInteract(Player* cel);
};