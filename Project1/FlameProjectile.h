#pragma once
#include "Projectile.h"

class Board;
class Entity;
class FlameProjectile : public Projectile
{
	int range = 25;
	int age = 0;//zmienne pomocnicze zwiazane z edycja wygladu i zasiegiem pocisku
public:
	void animate();
	FlameProjectile();
	FlameProjectile(Entity c, Board& board);
	void hitWall();
	bool hitEntity(Entity* toHit);

	bool move(int vel = -1);
};