#pragma once
#include "Weapon.h"

class Forcefield :public Weapon
{
public:
	Forcefield();
	void attack(Board& board, Entity& src);
};