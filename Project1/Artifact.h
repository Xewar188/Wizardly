#pragma once
#include "Entity.h"

class Artifact : public Entity
{
	int mod;
public:
	Artifact() { mod = 0; }
	Artifact(float width, float height, float x, float y, Color color, Board* board, int mode);
	void setAppearance() {}
	void onInteract(Player* cel);
	void dealDamage(int dmg, Projectile* src = NULL) {}
};