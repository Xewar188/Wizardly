#pragma once
#include "Weapon.h"
class Flamethrower : public Weapon
{
public:
	Flamethrower();
	Projectile* createProjectile(Board& board, Entity& src);
};