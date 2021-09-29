#pragma once
#include "Projectile.h"
#include "SFML/Graphics.hpp"
class Board;
class Entity;
class PlasmaswordProjectile : public Projectile
{
	Entity* src;
	float angleorg;
	float angle = 0;
	void setAppearance();
public:
	PlasmaswordProjectile();
	PlasmaswordProjectile(Entity* a, Board& board, sf::Color c);
	bool move(int vel = -1);
	void remove();

};