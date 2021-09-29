#pragma once
#include "Weapon.h"
class Bouncy :public Weapon
{
public:
	Bouncy();
	Projectile* createProjectile(Board& board, Entity& src);

};