#include "StartTile.h"
#include "Directions.h"
#include "Player.h"
#include <iostream>
#include "GameController.h"

StartTile::StartTile()
{
	state = 0;
}
StartTile::StartTile(Board* source, int x, int y)
{
	src = source;
	this->x = x;
	this->y = y;
	state = 0;
	rect = sf::RectangleShape(sf::Vector2f(src->getCellWidth(), src->getCellHeight()));
	rect.setPosition(src->getCellWidth() * x, src->getCellHeight() * y);
	for (int i = 20; i >= 1; i--)
	{
		toDraw.push_back(RectangleShape(Vector2f(src->getCellWidth() * i / 20, src->getCellHeight() * i / 20)));
		toDraw[toDraw.size() - 1].setPosition(rect.getPosition().x + src->getCellWidth() / 2 - toDraw[toDraw.size() - 1].getSize().x / 2,
			rect.getPosition().y + src->getCellHeight() / 2 - toDraw[toDraw.size() - 1].getSize().y / 2);
	}
	update();


	isTangible = false;
}
void StartTile::update()
{
	for (size_t i = 0; i < toDraw.size(); i++)
		toDraw[i].setFillColor(Color((int)(pow(sin(state + i * PI / 20), 2) * 255), 
									(int)(pow(sin(state + i * PI / 20), 2) * 255),
									(int)(pow(sin(state + i * PI / 20), 2) * 255)));
	state -= 0.02f;
}

void StartTile::onInteract(Player* cel)
{
	if (GameController::getPlayer()->getArtifactCounter() >= 4)
	{
		GameController::winGame();
	}
}
