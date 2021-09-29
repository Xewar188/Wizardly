#include "SpeedShrine.h"
#include "Player.h"
#include "MapTile.h"
#include "UsedShrine.h"

SpeedShrine::SpeedShrine()
{
}

SpeedShrine::SpeedShrine(Board* source, int x, int y)
{
	src = source;
	this->x = x;
	this->y = y;
	rect = sf::RectangleShape(sf::Vector2f(src->getCellWidth(), src->getCellHeight()));
	rect.setPosition(src->getCellWidth() * x, src->getCellHeight() * y);
	rect.setFillColor(sf::Color(0, 102, 204));

	toDraw.push_back(sf::RectangleShape(sf::Vector2f(src->getCellWidth() * 2 / 3, src->getCellHeight() * 2 / 3)));
	toDraw.push_back(sf::RectangleShape(sf::Vector2f(src->getCellWidth() / 3, src->getCellHeight() / 3)));
	toDraw[0].setFillColor(sf::Color(0, 153, 255));
	toDraw[1].setFillColor(sf::Color(51, 204, 255));
	toDraw[0].setPosition(rect.getPosition().x + src->getCellWidth() / 6, rect.getPosition().y + src->getCellHeight() / 6);
	toDraw[1].setPosition(rect.getPosition().x + src->getCellWidth() / 3, rect.getPosition().y + src->getCellHeight() / 3);
}

void SpeedShrine::onInteract(Player* cel)
{
	cel->board->getMap()->useShrine();
	cel->board->getMap()->update();
	cel->setVel(cel->getVel() + 1);
	src->changeCell(x, y, new UsedShrine(src, x, y));
}
