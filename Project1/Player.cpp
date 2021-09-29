#include "Player.h"
#include "Directions.h"
#include <iostream>
#include "GameController.h"
Player::Player()
{
}
Player::Player(float width, float height, float xa, float ya, Color color, Board* boarda)
{
	board = boarda;
	weight = 2;
	strength = 3;
	mode = FRIEND;
	vel = 6;


	body = RectangleShape(Vector2f(width, height));
	body.setPosition(Vector2f(xa, ya));
	setMapCoordinates();

	healthBar = RectangleShape(Vector2f(body.getSize().x * 2.25f, 5.0f));
	healthBarBackground = RectangleShape(Vector2f(body.getSize().x * 2.25f, 5));
	healthBar.setFillColor(Color::Red);
	healthBarBackground.setFillColor(Color(90, 90, 90));


	toDraw.push_back(RectangleShape(Vector2f(2.0f / 3.0f * width, 5.0f / 6.0f * height)));
	toDraw[0].setFillColor(color);
	direction = DOWN;

	maxHealth = 200;
	health = maxHealth;

	chart.addWeapons();
	isTangible = true;
	interactable = false;
	equipWeapon(chart.getCurrent());

	this->setAppearance();
}
void Player::interact()
{
	Entity* toInteract = NULL;
	sf::FloatRect interactArea;
	switch (direction)
	{
	case 1:
		interactArea = FloatRect((float)getCenterX() - 3, (float) body.getPosition().y - 20, 6.0f, 20.0f);
		break;
	case 2:
		interactArea = FloatRect((float) body.getPosition().x + body.getSize().x, (float)getCenterY() - 3, 20.0f, 6.0f);
		break;
	case 3:
		interactArea = FloatRect((float)getCenterX() - 3, (float)body.getPosition().y + body.getSize().y, 6.0f, 20.0f);
		break;
	case 4:
		interactArea = FloatRect((float)body.getPosition().x - 20, (float)getCenterY() - 3, 20.0f, 6.0f);
		break;
	}
	float curDistance = 1000000.0f;
	for (auto i = board->getEntityBeginPointer(); i != board->getEntityEndPointer(); i++)
	{
		
		if ((*i)->canBeInteracted() && distance(*i, this) < curDistance)
			if ((*i)->getBounds().intersects(interactArea))
			{
				curDistance = distance(*i, this);
				toInteract = *i;
				break;
			}
	}
	if (toInteract != NULL)
	{
		toInteract->onInteract(this);
		return;
	}
	if (board->getCell(x, y) != NULL && FloatRect(board->getCell(x, y)->getX() + board->getCellWidth()/4,
						board->getCell(x, y)->getY() + board->getCellHeight()/4,
						board->getCellWidth()/2, 
						board->getCellHeight()/2).contains(Vector2f((float) getCenterX(), (float) getCenterY())))
	{
		board->onInteract(this, x, y);
		
		return;
	}
	
	Vector2i dirToInteract = Vector2i(0,0);
	switch (direction) 
	{
	case UP:
		if (y > 0)
			dirToInteract = Vector2i(0,-1);
		break;
	case RIGHT:
		if (x < COLUMNS_NUMBER - 1)
			dirToInteract = Vector2i(1, 0);
		break;
	case DOWN:
		if (y < ROWS_NUMBER - 1)
			dirToInteract = Vector2i(0, 1);
		break;
	case LEFT:
		if (x > 0)
			dirToInteract = Vector2i(-1, 0);
		break;
	}
	if (board->getCell(x + dirToInteract.x, y + dirToInteract.y) != NULL &&
		interactArea.intersects(FloatRect(board->getCell(x + dirToInteract.x, y + dirToInteract.y)->getX(),
		board->getCell(x + dirToInteract.x, y + dirToInteract.y)->getY(),
		board->getCellWidth(), 
		board->getCellHeight())))
		board->onInteract(this, x + dirToInteract.x, y + dirToInteract.y);
	
}
void Player::equipWeapon(Weapon* wep)
{
	weapon = wep;
	body.setFillColor(weapon->getColor());
}
void Player::dealDamage(int dmg, Projectile* src)
{
	health -= dmg;
	if (health < 0)
		health = 0;
	healthBar.setSize(Vector2f(((float)health / (float)maxHealth) * healthBarBackground.getSize().x, healthBar.getSize().y));

}
void Player::setAppearance()
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
void Player::previousWeapon()
{
	chart.previousWeapon();
	equipWeapon(chart.getCurrent());

}
void Player::nextWeapon()
{
	chart.nextWeapon();
	equipWeapon(chart.getCurrent());
}
void Player::giveGold(int value)
{
	gold += value;
	if (gold > 999)
		gold = 999;
	GameController::updateGold(gold);
}
void Player::spendGold(int value)
{
	gold -= value;
	gold = std::max(0, gold);
}
int Player::getGold()
{
	return gold;
}
void Player::givePoints(int value)
{
	score += value;
}
int Player::getPoints()
{
	return score;
}
void Player::increaseArtifactCounter()
{
	artifactCounter++;
}
int Player::getArtifactCounter()
{
	return artifactCounter;
}
void Player::unlockWeapon()
{
	chart.unlockRandom();
}
void Player::increaseAttackSpeed(int value)
{
	attackSpeed += value;

}
void Player::addPiece(RectangleShape toAdd)
{
	toDraw.push_back(toAdd);
}
void Player::setVel(int vela)
{
	vel = vela;

	GameController::updateSpeed(vel - 5);
}
void Player::setStrength(int strengtha)
{
		strength = strengtha;  
		GameController::updateStrength(strength - weight);
}
void Player::clearPlayer()
{
	chart.clearWeapons();
}
void Player::increaseHealth(int value)
{
	maxHealth += value;
	heal(0);

}
