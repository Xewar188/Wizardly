#include "Chest.h"
#include "Player.h"
#include "Board.h"
#include "MapTile.h"
#include "Directions.h"
#include "GameController.h"
Chest::Chest()
{
}
Chest::Chest(float width, float height, float xa, float ya, Color color, Color secondary, Board* boarda)
{
	board = boarda;
	weight = 3;
	strength = 0;
	maxHealth = 150;
	health = maxHealth;
	body = RectangleShape(Vector2f(width, height));
	body.setPosition(Vector2f(xa, ya));
	setMapCoordinates();
	body.setOutlineColor(Color(0, 0, 0));
	body.setOutlineThickness(1);
	body.setFillColor(color);
	mode = NEUTRAL;

	toDraw.push_back(RectangleShape(Vector2f(2.0f / 3.0f * width, 2.0f / 7.0f * height)));
	toDraw.push_back(RectangleShape(Vector2f(2.0f / 3.0f * width, 2.0f / 7.0f * height)));
	toDraw[0].setFillColor(secondary);
	toDraw[1].setFillColor(secondary);
	toDraw.push_back(RectangleShape(Vector2f(1.0f / 12.0f * width, 2.0f / 7.0f * height)));
	toDraw[2].setFillColor(color);
	this->setAppearance();
	direction = UP;
	isTangible = true;
	interactable = true;
	board->getMap()->addChest();
	board->getMap()->update();
}
void Chest::onInteract(Player* cel)
{
	srand((unsigned int) time(NULL));
	if (rand() % 2 == 0)
	{
		cel->unlockWeapon();
		this->remove();
	}
	else
	{
		GameController::getPlayer()->giveGold(50);
		this->remove();
	}
}
void Chest::setAppearance()
{
	toDraw[0].setPosition(Vector2f(body.getPosition().x + 1.0f / 6.0f * body.getSize().x,
									body.getPosition().y + 1.0f / 7.0f * body.getSize().y));
	toDraw[1].setPosition(Vector2f(body.getPosition().x + 1.0f / 6.0f * body.getSize().x,
									body.getPosition().y + 4.0f / 7.0f * body.getSize().y));
	toDraw[2].setPosition(Vector2f(body.getPosition().x + 11.0f / 24.0f * body.getSize().x, 
									body.getPosition().y + 1.0f / 7.0f * body.getSize().y));

}
Chest::~Chest()
{
	board->getMap()->useChest();
	board->getMap()->update();
}
