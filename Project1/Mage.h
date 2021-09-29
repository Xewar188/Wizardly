#pragma once
#include "Entity.h"

class Mage :public Entity
{
public:
	Mage();//mode - 2
	~Mage();
	Mage(float width, float height, float x, float y, Color color, Board* board, Weapon* toEquip);
	void setAppearance();
	void update();
	void equipWeapon(Weapon* a);
};