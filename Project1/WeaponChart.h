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

class WeaponChart//musza znajdowac sie tu wszystkie instancje broni
{


	size_t currentlySelected = 0;
	std::vector<Weapon*> armory;//zbrojownia przechowujaca wszystkie bronie
public:
	WeaponChart();
	void clearWeapons();
	void addWeapons();
	void unlockRandom();
	Weapon* getCurrent();
	void nextWeapon();
	void previousWeapon();
};