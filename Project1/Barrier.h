#pragma once
#include "Weapon.h"
class Barrier : public Weapon
{
public:
	Barrier();
	void attack(Board& board, Entity& src);
};