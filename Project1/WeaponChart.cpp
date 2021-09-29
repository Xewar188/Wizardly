#include "WeaponChart.h"

WeaponChart::WeaponChart()
 {
		
	}

void WeaponChart::clearWeapons()
{
	for (Weapon* a : armory)
		delete a;
	armory.clear();
}

void WeaponChart::addWeapons()
{
	armory = { new MagicBolt(),
				   new Fireball(),
				   new Flamethrower(),
				   new Forcefield(),
				   new Barrier(),
				   new Plasmasword(),
				   new Homing(),
				   new Bouncy() };
}

void WeaponChart::unlockRandom()
{
	int unavaliableWeapons = 0;
	
	for (Weapon *w : armory) {
		if (!w->isAvaliable()) {
			unavaliableWeapons++;
		}
	}
	if (unavaliableWeapons == 0)
		return;
	int k = rand() % unavaliableWeapons + 1;
	int i = 0;

	while (k > 0)
	{
		i++;
		if (!armory[i]->isAvaliable())
			k--;
	}
	armory[i]->setAvaliablity(true);
}

Weapon* WeaponChart::getCurrent()
{
	return armory.at(currentlySelected);
}

void WeaponChart::nextWeapon()
{
	do
	{
		currentlySelected++;
		if (currentlySelected >= armory.size())
			currentlySelected = 0;
	} while (!armory[currentlySelected]->isAvaliable());
}

void WeaponChart::previousWeapon()
{
	do
	{
		currentlySelected--;
		currentlySelected = (size_t) std::min(armory.size() - 1, currentlySelected);
	} while (!armory[currentlySelected]->isAvaliable());
}
