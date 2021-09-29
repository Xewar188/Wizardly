#pragma once
#include "Weapon.h"
class Plasmasword : public Weapon
{
public:
	Plasmasword();
	void attack(Board& board, Entity& src);
};