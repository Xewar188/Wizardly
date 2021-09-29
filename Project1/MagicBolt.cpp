#include "MagicBolt.h"
#include "MagicBoltProjectile.h"
#include "Entity.h"

MagicBolt::MagicBolt()
{
	avaliable = true;
	cooldown = 20;
	weaponColor = Color(102, 0, 204);
	minCooldown = 10;
}

Projectile* MagicBolt::createProjectile(Board& board, Entity& src)
{
	return new MagicBoltProjectile(src, board);
}