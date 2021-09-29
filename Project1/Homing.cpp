#include "Homing.h"
#include "Board.h"
#include "HomingProjectile.h"
#include "Entity.h"

Homing::Homing()
{
	avaliable = false;
	cooldown = 30;
	weaponColor = Color(200, 0, 0);
	minCooldown = 20;
}

Projectile* Homing::createProjectile(Board& board, Entity& src)
{
	return new HomingProjectile(src, board);
}