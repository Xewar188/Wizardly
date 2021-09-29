#include "Barrier.h"
#include "Board.h"
#include "Projectile.h"
#include "BarrierEntity.h"

Barrier::Barrier()
{
	avaliable = false;
	cooldown = 100;
	weaponColor = Color(230, 230, 0);
	minCooldown = 50;
}

void Barrier::attack(Board& board, Entity& src)
{
	if (board.getTime() - src.getLastShootTime() >= std::max(cooldown - src.getAttackSpeed(), 10))
	{
		board.addEntity(new BarrierEntity(src, &board));
		src.startCooldown();
	}
}