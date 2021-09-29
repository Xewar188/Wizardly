#include "Bouncy.h"
#include "Board.h"
#include "BouncyProjectile.h"
#include "Entity.h"

Bouncy::Bouncy()
{
	avaliable = false;
	cooldown = 25;
	weaponColor = Color(85, 143, 41);
	minCooldown = 10;
}

Projectile* Bouncy::createProjectile(Board& board, Entity& src)
{
	return new BouncyProjectile(src, board);
}

