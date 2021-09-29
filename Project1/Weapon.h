#pragma once
#include <SFML\Graphics.hpp>
#include "Projectile.h"

class Board;
class Entity;
class Projectile;
class Weapon
{

protected:
	bool avaliable = true;//czy dostepny dla gracza
	int cooldown = 0;// czas po jakim mozemy zatakowac ponownie
	int minCooldown;
	sf::Color weaponColor = sf::Color::White;//kolor jakim sygnalizujemy typ broni
public:
	Weapon()
	{
		minCooldown = 10;
	}
	virtual void attack(Board& board, Entity& src);//atak na mapie board
	virtual Projectile* createProjectile(Board& board, Entity& src) { return new Projectile(); }
	sf::Color getColor();
	void changeColor(sf::Color c);
	bool isAvaliable();
	void setAvaliablity(bool b);
};







