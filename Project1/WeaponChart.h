#pragma once
#include <vector>
#include "MagicBolt.h"
#include "Fireball.h"
#include "Flamethrower.h"
#include "Forcefield.h"
#include "Plasmasword.h"
#include "Homing.h"
#include "Bouncy.h"
#include "Barrier.h"

class WeaponChart
{


	size_t currentlySelected = 0;
	std::vector<Weapon*> armory;
public:
	WeaponChart();
	void clearWeapons();
	void addWeapons();
	void unlockRandom();
	Weapon* getCurrent();
	void nextWeapon();
	void previousWeapon();
};