#pragma once
#include "Projectile.h"

class Board;
class Entity;
class BouncyProjectile : public Projectile
{
	int bounceNr = 2;
	void addDeathAnimation();
public:
	BouncyProjectile() {};
	BouncyProjectile(Entity a, Board& board);
	void hitWall();
	bool hitEntity(Entity* toHit);
	bool move(int vel = -1);

};