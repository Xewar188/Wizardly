#include "UsedShrine.h"
#include "Board.h"
UsedShrine::UsedShrine()
{
}

UsedShrine::UsedShrine(Board* source, int x, int y)
{
	src = source;
	this->x = x;
	this->y = y;
	rect = sf::RectangleShape(sf::Vector2f(src->getCellWidth(), src->getCellHeight()));
	rect.setPosition(src->getCellWidth() * x, src->getCellHeight() * y);
	rect.setFillColor(sf::Color(122, 122, 82));
	toDraw.push_back(sf::RectangleShape(sf::Vector2f(src->getCellWidth() * 2 / 3, src->getCellHeight() * 2 / 3)));
	toDraw.push_back(sf::RectangleShape(sf::Vector2f(src->getCellWidth() / 3, src->getCellHeight() / 3)));
	toDraw[0].setFillColor(sf::Color(153, 153, 102));
	toDraw[1].setFillColor(sf::Color(173, 173, 133));
	toDraw[0].setPosition(rect.getPosition().x + src->getCellWidth() / 6, rect.getPosition().y + src->getCellHeight() / 6);
	toDraw[1].setPosition(rect.getPosition().x + src->getCellWidth() / 3, rect.getPosition().y + src->getCellHeight() / 3);
}
