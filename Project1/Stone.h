#pragma once
#include "Cell.h"

class Stone : public Cell {
	int health;
public:

	Stone();
	Stone(Board* source, int x, int y);
	void onInteract(Player* cel);
	void hit(int dmg);
};