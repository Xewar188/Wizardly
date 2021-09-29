#pragma once
#include "Entity.h"

class Vendor : public Entity
{
	bool used = false;
protected:
	int cost;
public:
	Vendor();// mode -0
	Vendor(float width, float height, float x, float y, Board* board);
	void onInteract(Player* cel);
	void dealDamage(int dmg, Projectile* src = NULL) {}
	void setAppearance();
	virtual void buy(Player* target) {}
};