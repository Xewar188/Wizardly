#pragma once
#include "Cell.h"

class SpeedShrine : public Cell {
public:

	SpeedShrine();
	SpeedShrine(Board* source, int x, int y);
	void onInteract(Player* cel);
};