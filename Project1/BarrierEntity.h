#pragma once
#include "Entity.h"

class BarrierEntity : public Entity
{
	int age, maxAge;
	void createWideBody(int x, int y);
	void createHighBody(int x, int y);
public:
	BarrierEntity();
	BarrierEntity(Entity c, Board* board);
	void update();
	void onInteract(Player* cel);
	void dealDamage(int dmg, Projectile* src = NULL);
};