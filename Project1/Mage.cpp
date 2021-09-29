#include "Mage.h"
#include "Player.h"
#include "MathUtil.h"
#include "Directions.h"
#include "GameController.h"

Mage::Mage()
{
}
Mage::Mage(float width, float height, float xa, float ya, Color color, Board* boarda, Weapon* toEquip)
{
	board = boarda;
	weight = 2;
	strength = 3;
	mode = ENEMY;
	body = RectangleShape(Vector2f(width, height));
	body.setPosition(Vector2f(xa, ya));
	setMapCoordinates();

	healthBar = RectangleShape(Vector2f(body.getSize().x * 2, 4));
	healthBarBackground = RectangleShape(Vector2f(body.getSize().x * 2, 4));
	healthBar.setFillColor(Color::Red);
	healthBarBackground.setFillColor(Color(90, 90, 90));

	board->increaseEnemyCounter();
	randbase = rand();

	toDraw.push_back(RectangleShape(Vector2f(2.0f / 3.0f * width, 5.0f / 6.0f * height)));
	toDraw[0].setFillColor(color);
	direction = getDirectionFromInt(rand() % 4 + 1);
	this->setAppearance();
	maxHealth = 75;
	health = maxHealth;
	equipWeapon(toEquip);

	isTangible = true;
	interactable = false;
}
void Mage::setAppearance()
{
	switch (direction)
	{
	case 1:
		toDraw[0].setRotation(0);
		toDraw[0].setPosition(Vector2f(body.getPosition().x + body.getSize().x / 6,
										body.getPosition().y));

		break;
	case 2:
		toDraw[0].setRotation(270);
		toDraw[0].setPosition(Vector2f(body.getPosition().x + body.getSize().x / 6,
										body.getPosition().y + body.getSize().y * 5 / 6));
		break;
	case 3:
		toDraw[0].setRotation(0);
		toDraw[0].setPosition(Vector2f(body.getPosition().x + body.getSize().x / 6,
										body.getPosition().y + body.getSize().y / 6));
		break;
	case 4:
		toDraw[0].setRotation(270);
		toDraw[0].setPosition(Vector2f(body.getPosition().x,
										body.getPosition().y + body.getSize().y * 5 / 6));
		break;

	}
	healthBar.setPosition(getCenterX() - healthBarBackground.getSize().x / 2, body.getPosition().y - 10);
	healthBarBackground.setPosition(healthBar.getPosition());

}
void Mage::update()
{
	if ((int)abs(rand()) % 5 == 0)
		this->attack();
	if (rand() % 20 == 0)
	{
		if (abs(this->body.getPosition().y - GameController::getPlayer()->getPosition().y) < abs(this->body.getPosition().x - GameController::getPlayer()->getPosition().x))
		{
			this->setDir(3 + sgn(this->body.getPosition().x - GameController::getPlayer()->getPosition().x));

		}
		else
		{

			this->setDir(2 - sgn(this->body.getPosition().y - GameController::getPlayer()->getPosition().y));
		}

		this->setAppearance();
		this->lastShot = this->board->getTime();
	}
	Entity::update();
}
void Mage::equipWeapon(Weapon* wep)
{
	weapon = wep;
	body.setFillColor(weapon->getColor());
}
Mage::~Mage()
{
	GameController::getPlayer()->giveGold(5);
	GameController::getPlayer()->givePoints(5);
	board->decreaseEnemyCounter();
	delete weapon;
}
