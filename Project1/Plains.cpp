#include "Plains.h"
#include "Board.h"
#include "Stone.h"
#include "Player.h"
Plains::Plains()
{
}

Plains::Plains(Board* source, int x, int y)
{
	src = source;
	this->x = x;
	this->y = y;
	rect = sf::RectangleShape(sf::Vector2f(src->getCellWidth(), src->getCellHeight()));
	rect.setPosition(src->getCellWidth() * x, src->getCellHeight() * y);
	rect.setFillColor(sf::Color(51, 204, 51));
}

void Plains::onInteract(Player* cel)
{
}
