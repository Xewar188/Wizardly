#include "Fireball.h"
#include "Board.h"
#include "FireballProjectile.h"
#include "Entity.h"

Fireball::Fireball()
{
	avaliable = false;
	cooldown = 30;
	weaponColor = Color(51, 153, 255);
	minCooldown = 15;
}

Projectile* Fireball::createProjectile(Board& board, Entity& src)
{
	return new FireballProjectile(src, board);
}
