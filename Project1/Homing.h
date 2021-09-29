#pragma once
#include "Weapon.h"

class Homing : public Weapon
{
public:
	Homing();
	Projectile* createProjectile(Board& board, Entity& src);
};