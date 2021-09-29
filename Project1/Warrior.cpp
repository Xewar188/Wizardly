#include "Warrior.h"
#include "Player.h"
#include "MathUtil.h"
#include "Directions.h"
#include <iostream>
#include "GameController.h"
Warrior::Warrior()
{
}
Warrior::Warrior(float width, float height, float xa, float ya, Color color, Color secondary, Board* boarda)
{
	board = boarda;
	weight = 3;
	strength = 6;
	mode = ENEMY;
	body = RectangleShape(Vector2f(width, height));
	healthBar = RectangleShape(Vector2f(body.getSize().x * 2, 4));
	healthBarBackground = RectangleShape(Vector2f(body.getSize().x * 2, 4));
	healthBar.setFillColor(Color::Red);
	healthBarBackground.setFillColor(Color(90, 90, 90));
	vel = 3;
	lastShot = rand()% 48;

	body.setPosition(Vector2f(xa, ya));
	setMapCoordinates();
	toDraw.push_back(RectangleShape(Vector2f(5.0f / 3.0f * width, 1.0f / 3.0f * height)));
	toDraw[0].setFillColor(color);
	toDraw.push_back(RectangleShape(Vector2f(width / 6, height / 2)));
	toDraw[1].setFillColor(color);
	direction = getDirectionFromInt(rand() % 4 + 1);
	this->setAppearance();
	maxHealth = 100;
	health = maxHealth;

	Entity::equipWeapon(new Plasmasword());
	weapon->changeColor(secondary);
	body.setFillColor(secondary);
	board->increaseEnemyCounter();
	isTangible = true;
	interactable = false;
}
void Warrior::setAppearance()
{
	switch (direction)
	{
	case UP:
		toDraw[0].setRotation(0);
		toDraw[1].setRotation(0);
		toDraw[0].setPosition(Vector2f(getCenterX() - toDraw[0].getSize().x / 2, 
										body.getPosition().y + body.getSize().y));
		toDraw[1].setPosition(Vector2f(getCenterX() - toDraw[1].getSize().x / 2,
										getCenterY() - toDraw[1].getSize().y / 2));

		break;
	case RIGHT:
		toDraw[0].setRotation(270);
		toDraw[1].setRotation(270);
		toDraw[0].setPosition(Vector2f(body.getPosition().x - toDraw[0].getSize().y, 
										getCenterY() + body.getSize().y - toDraw[1].getSize().y / 2));
		toDraw[1].setPosition(Vector2f(getCenterX() - toDraw[1].getSize().y / 2,
										getCenterY() + toDraw[1].getSize().x / 2));
		break;
	case DOWN:
		toDraw[0].setRotation(0);
		toDraw[1].setRotation(0);
		toDraw[0].setPosition(Vector2f(getCenterX() - toDraw[0].getSize().x / 2,
										body.getPosition().y - toDraw[0].getSize().y));
		toDraw[1].setPosition(Vector2f(getCenterX() - toDraw[1].getSize().x / 2,
										getCenterY() - toDraw[1].getSize().y / 2));
		break;
	case LEFT:
		toDraw[0].setRotation(270);
		toDraw[1].setRotation(270);
		toDraw[0].setPosition(Vector2f(body.getPosition().x + body.getSize().x, 
										getCenterY() + body.getSize().y - toDraw[0].getSize().y / 2));
		toDraw[1].setPosition(Vector2f(getCenterX() - toDraw[1].getSize().y / 2,
										getCenterY() + toDraw[1].getSize().x / 2));
		break;

	}
	healthBar.setPosition(getCenterX() - healthBarBackground.getSize().x / 2, 
							body.getPosition().y - 25);
	healthBarBackground.setPosition(healthBar.getPosition());
}
void Warrior::update()
{
	this->attack();

	if (path.size() == 0 
		|| !(path[0].x == GameController::getPlayer()->getMapCellX() && path[0].y == GameController::getPlayer()->getMapCellY())
		|| !(path[path.size() - 1].x == x && path[path.size() - 1].y == y
			|| path[path.size() - 2].x == x && path[path.size() - 2].y == y))
	{
		this->findPath();
		if (path.size() >= 2) {
			int newDir = (path[path.size() - 2].x - x)
				+ (path[path.size() - 2].y - y) * 2;
			switch (newDir)
			{
			case 1:
				setDir(RIGHT);
				break;
			case -1:
				setDir(LEFT);
				break;
			case 2:
				setDir(DOWN);
				break;
			case -2:
				setDir(UP);
				break;
			}
		}
	}
	
	if (path.size() > 2)
	{
		if (path[path.size() - 2].x == x && path[path.size() - 2].y == y)
			path.pop_back();
		int newDir = (path[path.size() - 2].x - x)
			+ (path[path.size() - 2].y - y) * 2;
		switch (newDir)
		{
		case 1 :
			if (abs(board->getCellHeight() * (path[path.size() - 2].y + 1.0 / 2.0) - getCenterY()) < 2)
				setDir(RIGHT);
			break;
		case -1:
			if (abs(board->getCellHeight() * (path[path.size() - 2].y + 1.0 / 2.0) - getCenterY()) < 2)
				setDir(LEFT);
			break;
		case 2:
			if (abs(board->getCellWidth() * (path[path.size() - 2].x + 1.0 / 2.0) - getCenterX()) < 2)
				setDir(DOWN);
			break;
		case -2:
			if (abs(board->getCellWidth() * (path[path.size() - 2].x + 1.0 / 2.0) - getCenterX()) < 2)
				setDir(UP);
			break;
		}
		if (!this->move(this->direction, this->strength)) {
			setDir(turnClockwise(this->direction, 1  + 2 * (rand()%2)));
		}
	}
	else
	{
		bool moved = false;
		if (abs(floor(body.getPosition().x - GameController::getPlayer()->getPosition().x)) >= vel)
		{
			this->setDir(3 + sgn(body.getPosition().x - GameController::getPlayer()->getPosition().x));
			moved = this->move(this->direction, this->strength);

		}
		if (abs(floor(body.getPosition().y - GameController::getPlayer()->getPosition().y)) >= vel && !moved)
		{
			this->setDir(2 - sgn(body.getPosition().y - GameController::getPlayer()->getPosition().y));
			moved = this->move(this->direction, this->strength);

		}

	}

	
	Entity::update();
}

Warrior::~Warrior()
{
	GameController::getPlayer()->giveGold(10);
	GameController::getPlayer()->givePoints(10);
	board->decreaseEnemyCounter();
	delete weapon;
}