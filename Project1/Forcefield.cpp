#include "Forcefield.h"
#include "Board.h"
#include "ForcefieldProjectile.h"
#include "Entity.h"
Forcefield::Forcefield()
{
	avaliable = false;
	cooldown = 40;
	weaponColor = Color(138, 254, 255);
}

void Forcefield::attack(Board& board, Entity& src)
{

	if (board.getTime() - src.getLastShootTime() >= std::max(cooldown - src.getAttackSpeed(), 20))
	{
		for (int i = 0; i < 10; i++)
			board.addProjectile(board.currentId(), new ForcefieldProjectile(src, board, i, 10));
		src.startCooldown();
	}
}