#include "Cell.h"
#include "Entity.h"
#include "Player.h"
#include "MapTile.h"
Cell::Cell() {
	x = 0;
	y = 0;
	src = NULL;
}



float Cell::getX()
{
	return rect.getPosition().x;
}

float Cell::getY()
{
	return rect.getPosition().y;
}

void Cell::draw(sf::RenderTarget& window, sf::RenderStates state) const
{
	window.draw(rect);
	for (RectangleShape cur : toDraw)
		window.draw(cur);
}

void Cell::setFilled(bool isFilled)
{
	filled = isFilled;
}

bool Cell::isFilled()
{
	return filled;
}

bool Cell::isCellTangible()
{
	return isTangible;
}


void Cell::onInteract(Player* cel) {  }


