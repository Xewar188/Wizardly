#pragma once
#include "Entity.h"

class Healpoint : public Entity
{
	int uses = 0;
public:
	Healpoint();
	Healpoint(float width, float height, float x, float y, Board* board);
	void onInteract(Player* cel);
	void dealDamage(int dmg, Projectile* src = NULL) {}
	void setAppearance();


};