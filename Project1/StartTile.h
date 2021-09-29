#pragma once
#include "Cell.h"

class StartTile : public Cell {
	float state;
public:

	StartTile();
	StartTile(Board* source, int x, int y);
	void update();
	void onInteract(Player* cel);
};