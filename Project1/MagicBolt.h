#pragma once
#include "Board.h"
#include "Weapon.h"
class MagicBolt : public Weapon
{
public:
	MagicBolt();
	Projectile* createProjectile(Board& board, Entity& src);

};