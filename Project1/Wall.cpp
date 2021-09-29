#pragma once
#include "Wall.h"
#include "Board.h"
Wall::Wall()
{
}

Wall::Wall(Board *source, int x, int y)
{
	isTangible = true;
	src = source;
	this->x = x;
	this->y = y;
	rect = sf::RectangleShape(sf::Vector2f(src->getCellWidth(), src->getCellHeight()));
	rect.setPosition(src->getCellWidth() * x, src->getCellHeight() * y);
	rect.setFillColor(sf::Color(37, 89, 0));
}
