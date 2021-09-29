#include "Flamethrower.h"
#include "Board.h"
#include "FlameProjectile.h"
#include "Entity.h"

Flamethrower::Flamethrower()
{
	avaliable = false;
	cooldown = 8;
	weaponColor = Color(255, 140, 0);
	minCooldown = 4;
}

Projectile* Flamethrower::createProjectile(Board& board, Entity& src)
{
	return new FlameProjectile(src, board);
}
