#pragma once
#include "Projectile.h"

class Board;
class Entity;
class FireballProjectile : public Projectile
{
	int age = 0;
	void addDeathAnimation();
public:
	FireballProjectile();
	FireballProjectile(Entity c, Board& board);
	float state;
	void hitWall();
	bool hitEntity(Entity* toHit);
	void setAppearance();

	bool move(int vel = -1);
	void animate();
};