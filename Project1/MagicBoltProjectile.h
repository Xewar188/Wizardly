#pragma once
#include "Projectile.h"

class Board;
class Entity;
class MagicBoltProjectile : public Projectile 
{
	int age = 0;
	float state = 0;
	void addDeathAnimation();
public:
	MagicBoltProjectile();
	MagicBoltProjectile(Entity c, Board& board);


	void hitWall();
	bool hitEntity(Entity* toHit);
	bool move(int vel = -1);
	void animate();
};