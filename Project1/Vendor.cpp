#include "Vendor.h"
#include "Player.h"
#include "Board.h"
#include "MapTile.h"
#include "Directions.h"
#include <iostream>
#include "GameController.h"

Vendor::Vendor()
{

}
Vendor::Vendor(float width, float height, float xa, float ya, Board* boarda)
{
	board = boarda;
	weight = 4;
	strength = 0;
	mode = NEUTRAL;
	cost = 0;
	body = RectangleShape(Vector2f(width, height));
	setMapCoordinates();
	direction = UP;
	movable = true;
	isTangible = true;
	interactable = true;
	body.setFillColor(Color(255, 225, 0));
	body.setPosition(xa, ya);
	toDraw.push_back(RectangleShape(Vector2f(width * 2 / 3, height * 2 / 3)));
	toDraw[0].setPosition(xa + width / 6, ya + height / 6);
	board->getMap()->addVendor();
	board->getMap()->update();
}
void Vendor::onInteract(Player* cel)
{
	if (cel->getGold() >= this->cost && !used)
	{
		cel->giveGold(-this->cost);
		this->buy(cel);
		used = true;
		toDraw[0].setFillColor(Color(0, 153, 255));
		cel->board->getMap()->useVendor();
		cel->board->getMap()->update();
	}
	else if (!used)
	{
		bool isEnd = false;
		for (int i = 0; i < 20; i++)
		{
			std::stringstream temp;
			temp << cost;
			std::string temps;
			temp >> temps;
			Text toAdd = Text(temps, *GameController::getFont());
			toAdd.setPosition(body.getPosition().x - 13, body.getPosition().y - body.getSize().y * 5 / 4);
			toAdd.setFillColor(Color(255, 225, 0, 255 - i * 10));
			toAdd.setCharacterSize(30);
			board->addTextToAnimate(toAdd, i);
		}
	}
}
void Vendor::setAppearance()
{
	toDraw[0].setPosition(body.getPosition().x + body.getSize().x / 6,
							body.getPosition().y + body.getSize().y / 6);
}