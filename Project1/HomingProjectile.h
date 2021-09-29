#pragma once
#include "Projectile.h"

class Board;
class Entity;
class HomingProjectile : public Projectile
{
	Entity* target = NULL;//zmienne pomocnicze zwiazane z poruszaniem sie pocisku
public:
	HomingProjectile() {}
	HomingProjectile(Entity& a, Board& board);
	void hitWall();
	bool hitEntity(Entity* toHit);
	void setAppearance();
	bool move(int vel = -1);
};