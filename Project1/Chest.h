#pragma once
#include "Entity.h"

class Chest :public Entity
{
public:
	Chest();
	Chest(float width, float height, float x, float y, Color color, Color secondary, Board* board);
	void onInteract(Player* cel);
	void setAppearance();
	~Chest();
};