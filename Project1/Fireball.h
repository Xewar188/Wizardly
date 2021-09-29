#pragma once
#include "Weapon.h"
class Fireball :public Weapon
{
public:
	Fireball();
	Projectile* createProjectile(Board& board, Entity& src);

};