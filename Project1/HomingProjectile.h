#pragma once
#include "Projectile.h"

class Board;
class Entity;
class HomingProjectile : public Projectile
{
	Entity* target = NULL;
public:
	HomingProjectile() {}
	HomingProjectile(Entity& a, Board& board);
	void hitWall();
	bool hitEntity(Entity* toHit);
	void setAppearance();
	bool move(int vel = -1);
};