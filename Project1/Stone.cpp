#include "Stone.h"
#include "Board.h"
#include "Plains.h"

Stone::Stone()
{
	health = 0;
}

Stone::Stone(Board* source, int x, int y)
{
	health = 25;
	isTangible = true;
	src = source;
	this->x = x;
	this->y = y;
	rect = sf::RectangleShape(sf::Vector2f(src->getCellWidth(), src->getCellHeight()));
	rect.setPosition(src->getCellWidth() * x, src->getCellHeight() * y);
	rect.setFillColor(sf::Color(139, 140, 147));
}

void Stone::onInteract(Player* cel)
{
}

void Stone::hit(int dmg)
{
	health -= dmg;
	if (health <= 0)
		src->changeCell(x, y, new Plains(src, x, y));
	else
		rect.setFillColor(sf::Color(139 +  (25 - health) ,
									140 +  (25 - health) ,
									147 +  (25 -  health)));
}
