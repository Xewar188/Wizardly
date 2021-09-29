#pragma once
#include <SFML\Graphics.hpp>
#include "Projectile.h"

class Board;
class Entity;
class Projectile;
class Weapon
{

protected:
	bool avaliable = true;
	int cooldown = 0;
	int minCooldown;
	sf::Color weaponColor = sf::Color::White;
public:
	Weapon()
	{
		minCooldown = 10;
	}
	virtual void attack(Board& board, Entity& src);
	virtual Projectile* createProjectile(Board& board, Entity& src) { return new Projectile(); }
	sf::Color getColor();
	void changeColor(sf::Color c);
	bool isAvaliable();
	void setAvaliablity(bool b);
};







