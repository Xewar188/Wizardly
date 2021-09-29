#include "Weapon.h"
#include "Board.h"
#include "Entity.h"

void Weapon::attack(Board& board, Entity& src)
{
	if (board.getTime() - src.getLastShootTime() >= std::max(cooldown - src.getAttackSpeed(), minCooldown))
	{
		board.addProjectile(board.currentId(), this->createProjectile(board, src));
		src.startCooldown();
	}
}

sf::Color Weapon::getColor()
{
    return weaponColor;
}

void Weapon::changeColor(sf::Color c)
{
   weaponColor = c;
}

bool Weapon::isAvaliable()
{
    return avaliable;
}

void Weapon::setAvaliablity(bool b)
{
    avaliable = b;
}
