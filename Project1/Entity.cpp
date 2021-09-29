#include "pch.h"
#include "Entity.h"
#include "Player.h"
#include<vector>
#include <list>
#include<iostream>
#include "Map.h"
#include "Directions.h"
#include "GameController.h"

Entity::Entity(float width, float height, float xa, float ya, Color color, Color secondary, Board* boarda)
{
	direction = DOWN;
	health = 0;
	maxHealth = 0;
	speed = 1;

	x = 0;
	y = 0;
	board = boarda;
}
Entity::Entity()
{
	body = RectangleShape(Vector2f(0, 0));
	x = (int)std::floor((0 + body.getSize().x / 2) / 1);
	y = (int)std::floor((0 + body.getSize().y / 2) / 1);
	Entity::health = 1;
	Entity::maxHealth = 1;
	body.setPosition(Vector2f(0, 0));
	direction = DOWN;
}
Entity::~Entity()
{
	for (Projectile* p : personalProjectiles)
		delete p;
}
bool Entity::equals(Entity* toCompare)
{
	return body.getPosition().x == toCompare->body.getPosition().x 
		&& body.getPosition().y == toCompare->body.getPosition().y;
}
void Entity::removePersonalProjectile(Projectile* toRemove)
{
	projectilesToRemove.push_back(toRemove);
}
void Entity::setMapCoordinates()
{
	x = board->getCellX(getCenterX());
	y = board->getCellY(getCenterY());
}
void Entity::remove()
{
	board->removeEntity(this);
}
int Entity::getCenterX()
{
	return (int) body.getPosition().x + (int) body.getSize().x / 2;
}
int Entity::getCenterY()
{
	return (int) body.getPosition().y + (int) body.getSize().y / 2;
}
int Entity::getAttackSpeed()
{
	return attackSpeed;
}
int Entity::getLastShootTime()
{
	return (int) lastShot;
}
void Entity::draw(RenderTarget& window, RenderStates state) const
{
	
	window.draw(body, state);

	for(int i = 0; i < (int)toDraw.size(); i++)
		window.draw(toDraw[i], state);

	window.draw(healthBarBackground);
	window.draw(healthBar);

	for (int i = 0; i < (int)personalProjectiles.size(); i++)
		window.draw(*personalProjectiles[i]);
}
bool Entity::move(int dir, int force)
{
	bool a = false;
	for (int i = 0; i < vel; i++)
	{
		speed = 1;
		a = move(dir, speed, force);
	}
	setAppearance();
	return a;
}
bool Entity::isAgainstWall(Vector2i direction)
{
	switch (direction.y)
	{
	case 1:
		if (y >= ROWS_NUMBER - 1)
			return false;
		break;
	case -1:
		if (y <= 0)
			return false;
		break;
	}
	switch (direction.x)
	{
	case 1:
		if (x >= COLUMNS_NUMBER - 1)
			return false;
		break;
	case -1:
		if (x <= 0)
			return false;
		break;
	}
	bool middle, first, last;
	int targetCellX = x + direction.x;
	int targetCellY = y + direction.y;

	FloatRect middleRectangle = FloatRect((float)targetCellX * board->getCellWidth() + abs(direction.y),
											(float)targetCellY * board->getCellHeight() + abs(direction.x),
											(float)board->getCellWidth() + 1 - 2 * abs(direction.y),
											(float)board->getCellHeight() + 1 - 2 * abs(direction.x));
	middle = board->getCell(targetCellX, targetCellY) == NULL ? false : board->getCell(targetCellX, targetCellY)->isCellTangible();
	targetCellX = x + direction.x + direction.y;
	targetCellY = y + direction.y + direction.x;
	FloatRect firstRectangle = FloatRect((float)targetCellX * board->getCellWidth() + abs(direction.y),
										(float)targetCellY * board->getCellHeight() + abs(direction.x),
										(float)board->getCellWidth() + 1 - 2 * abs(direction.y),
										(float)board->getCellHeight() + 1 - 2 * abs(direction.x));
	first = board->getCell(targetCellX, targetCellY) == NULL ? false : board->getCell(targetCellX, targetCellY)->isCellTangible();
	targetCellX = x + direction.x - direction.y;
	targetCellY = y + direction.y - direction.x;
	FloatRect lastRectangle = FloatRect((float)targetCellX * board->getCellWidth() + abs(direction.y),
										(float)	targetCellY * board->getCellHeight() + abs(direction.x),
										(float)board->getCellWidth() + 1 - 2 * abs(direction.y),
										(float)board->getCellHeight() + 1 - 2 * abs(direction.x));
	last = board->getCell(targetCellX, targetCellY) == NULL ? false : board->getCell(targetCellX, targetCellY)->isCellTangible();
	return	(body.getGlobalBounds().intersects(middleRectangle) && middle)
			|| (body.getGlobalBounds().intersects(firstRectangle) && first)
			|| (body.getGlobalBounds().intersects(lastRectangle) && last);
}
bool Entity::tryMovingEntities(int force, float& speed, Vector2i direction)
{
	bool hasMoved = false;
	float speedmod = 2.0f / (2.0f + (float)force) + 1.0f;
	std::vector<Entity*> help;
	FloatRect pushArea;
	Direction toMove;
	switch (direction.y)
	{
	case 1:
		toMove = DOWN;
		pushArea = FloatRect(body.getPosition().x, body.getPosition().y + body.getSize().y, body.getSize().x, 1);
		break;
	case -1:
		toMove = UP;
		pushArea = FloatRect(body.getPosition().x, body.getPosition().y - 1, body.getSize().x, 1);
		break;
	}
	switch (direction.x)
	{
	case 1:
		toMove = RIGHT;
		pushArea = FloatRect(body.getPosition().x + body.getSize().x, body.getPosition().y, 1, body.getSize().y);
		break;
	case -1:
		toMove = LEFT;
		pushArea = FloatRect(body.getPosition().x - 1, body.getPosition().y, 1, body.getSize().y);
		break;
	}
	for (auto i = board->getEntityBeginPointer(); i != board->getEntityEndPointer(); i++)
	{
		if (!this->equals(*i) && (*i)->isTangible
			&& pushArea.intersects((*i)->getBounds()))
		{

			help.push_back(*i);
		}
	}
	int k = 0;
	for (int i = 0; i < (int)help.size(); i++)
	{
		if (help[i]->movable)
		{
			speed /= speedmod;
			if (help[i]->move((int)toMove, speed, force))
			{
				k++;
			}
		}
	}
	if (k == help.size())
	{
		body.move(speed * direction.x, speed * direction.y);
		return true;
	}
	return false;
}
void Entity::changeTile()
{
	if (board->getCell(x,y) != NULL && board->getCell(x, y)->getY() > getCenterY())
	{
		y--;
	}
	if (board->getCell(x, y) != NULL && board->getCell(x, y)->getY() + board->getCellHeight() < getCenterY())
	{
		y++;
	}
	if (board->getCell(x, y) != NULL && board->getCell(x, y)->getX() > getCenterX())
	{
		x--;
	}
	if (board->getCell(x, y) != NULL && board->getCell(x, y)->getX() + board->getCellWidth() < getCenterX())
	{
		x++;
	}
}
void Entity::checkForMapChange()
{
	if (y < 0)
	{
		if (mode == -1)
		{
			y = ROWS_NUMBER - 1;
			body.setPosition(body.getPosition().x, std::floor(board->getCellHeight() * ROWS_NUMBER - body.getSize().y / 2));
			GameController::changeBoard(0, -1);
		}
		else
		{
			y = 2;
			body.setPosition(body.getPosition().x, std::floor(board->getCellHeight() * 2));
		}
	}
	if (y >= ROWS_NUMBER)
	{
		if (mode == -1)
		{
			y = 0;
			body.setPosition(body.getPosition().x, body.getSize().y / 2);
			GameController::changeBoard(0, 1);
		}
		else
		{
			y = ROWS_NUMBER - 3;
			body.setPosition(body.getPosition().x, board->getWidth() - std::floor(board->getCellHeight() * 2));
		}
	}
	if (x < 0)
	{
		if (mode == -1)
		{
			x = COLUMNS_NUMBER - 1;
			body.setPosition(std::floor(board->getCellWidth() * COLUMNS_NUMBER - body.getSize().x / 2), body.getPosition().y);
			GameController::changeBoard(-1, 0);
		}
		else
		{
			x = 2;
			body.setPosition(std::floor(board->getCellWidth() * 2), body.getPosition().y);
		}
	}
	if (x >= COLUMNS_NUMBER)
	{
		if (mode == -1)
		{
			x = 0;
			body.setPosition(body.getSize().x / 2, body.getPosition().y);
			GameController::changeBoard(1, 0);
		}
		else
		{
			x = COLUMNS_NUMBER - 3;
			body.setPosition(board->getHeight() - std::floor(board->getCellWidth() * 2), body.getPosition().y);
		}
	}

}
bool Entity::move(int dir,  float &speed, int force)
{

	force -= this->weight;
	if (force < 0 || !movable)
	{
		return false;
	}
	Vector2i moveDir;
	
	switch (dir)
	{
		
	case UP:
		if (y == 0 && mode != -1)
			return false;
		moveDir = Vector2i(0, -1);
		break;
	case RIGHT:
		if (x == COLUMNS_NUMBER - 1 && mode != -1)
			return false;
		moveDir = Vector2i(1, 0);
		break;
	case DOWN:
		if (y == ROWS_NUMBER - 1 && mode != -1)
			return false;
		moveDir = Vector2i(0, 1);
		break;
	case LEFT:
		if (x == 0 && mode != -1)
			return false;
		moveDir = Vector2i(-1, 0);
		break;
	}
	if (isAgainstWall(moveDir)) {
		return false;
	}
	if (!tryMovingEntities(force, speed, moveDir)) {
		return false;
	}
	changeTile();
	checkForMapChange();
	this->setAppearance();
	return true;
}
void Entity::setAppearance(){}
float Entity::distance(Entity *e1, Entity *e2)
{
	return (float) sqrt((e1->getCenterX() - e2->getCenterX()) * (e1->getCenterX() - e2->getCenterX()) +
						(e1->getCenterY() - e2->getCenterY()) * (e1->getCenterY() - e2->getCenterY()));
}
void Entity::onInteract(Player* cel){}
void Entity::dealDamage(int dmg,Projectile* src)
{
	health -= dmg;
	healthBar.setSize(Vector2f(((float)health / (float)maxHealth) * healthBarBackground.getSize().x, 4));
	if (!isAlive())
	{
		this->remove();
	}
}
void Entity::attack()
{	
	weapon->attack(*board, *this);
}
void Entity::setDir(int d)
{
	direction = getDirectionFromInt(d);
	setAppearance();
}
void Entity::update()
{
	 for (int i = 0; i < (int)personalProjectiles.size(); i++)
		 personalProjectiles[i]->move();

	 for (Projectile *toRemove: projectilesToRemove)
		for (int i = 0; i < (int)personalProjectiles.size(); i++)
		{
			if (personalProjectiles[i]->equals(toRemove))
			{
				personalProjectiles.erase(personalProjectiles.begin() + i);
				delete toRemove;
				break;
			}
		}
	 projectilesToRemove.clear();
}
void Entity::heal(int h)
{
	health += h;
	
	if (health > maxHealth)
		health = maxHealth;
	healthBar.setSize(Vector2f(((float)health / (float)maxHealth) * healthBarBackground.getSize().x, healthBarBackground.getSize().y));
}
void Entity::equipWeapon(Weapon* wep)
{
	weapon = wep;
}
void Entity::startCooldown()
{
	this->lastShot = board->getTime();
}
Direction Entity::getDirection()
{
	return direction;
}
Vector2f Entity::getPosition()
{
	return body.getPosition();
}
Vector2f Entity::getSize()
{
	return body.getSize();
}
int Entity::getMapCellX()
{
	return x;
}
int Entity::getMapCellY()
{
	return y;
}
int Entity::getMode()
{
	return mode;
}
int Entity::getVel()
{
	return vel;
}
int Entity::getStrength()
{
	return strength;
}
FloatRect Entity::getBounds()
{
	return body.getGlobalBounds();
}
bool Entity::isInteractable()
{
	return interactable;
}
bool Entity::isAlive()
{
	return health > 0;
}
bool Entity::canBeInteracted()
{
	return interactable;
}
bool Entity::doesCollide()
{
	return isTangible;
}
int Entity::getMaxHealth()
{
	return maxHealth;
}
int Entity::getHealth()
{
	return health;
}
void Entity::addProjectile(Projectile* p)
{
	personalProjectiles.push_back(p);
}
class CustomComparator
{
	int** valueArray;
public:
	CustomComparator(int** valArray) {
		valueArray = valArray;
	}
	bool operator () (const Vector2i& lhs, const Vector2i& rhs) {
		return valueArray[lhs.x][lhs.y] < valueArray[rhs.x][rhs.y];
	}

};
void Entity::findPath()
{
	int distance[COLUMNS_NUMBER][ROWS_NUMBER] = { 0 };
	Vector2i way[COLUMNS_NUMBER][ROWS_NUMBER];
	bool isOpen[COLUMNS_NUMBER][ROWS_NUMBER] = { 0 };
	isOpen[x][y] = true;
	path.clear();
	distance[x][y] = 0;
	std::list<Vector2i> openCells;
	openCells.push_back(Vector2i(x, y));
	while (openCells.size() > 0)
	{
		int curX = openCells.front().x;
		int curY = openCells.front().y;

		openCells.pop_front();
		if (curX == GameController::getPlayer()->getMapCellX() && curY == GameController::getPlayer()->getMapCellY())
		{
			break;
		}
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (abs(j) + abs(i) != 1)
				{
					continue;
				}
				if (curX + i < 0 || curX + i > COLUMNS_NUMBER - 1
					|| curY + j < 0 || curY + j > ROWS_NUMBER - 1)
				{
					continue;
				}					
				if (board->getCell(curX + i, curY + j)->isCellTangible())
				{
					isOpen[curX + i][curY + j] = true;
					continue;
				}
				if (!isOpen[curX + i][curY + j])
				{
					openCells.push_back(Vector2i(curX + i, curY + j));
					isOpen[curX + i][curY + j] = true;
					distance[curX + i][curY + j] = distance[curX][curY] + 1;
					way[curX + i][curY + j] = Vector2i(curX, curY);
					
				}

				if (distance[curX + i][curY + j] > distance[curX][curY] + 1)
				{
					distance[curX + i][curY + j] = distance[curX][curY] + 1;
					way[curX + i][curY + j] = Vector2i(curX, curY);
				}

			}
	}

	Vector2i place;
	
	place = Vector2i(GameController::getPlayer()->getMapCellX(), GameController::getPlayer()->getMapCellY());

	if (distance[place.x][place.y] == 0)
		return;

	while (place.x != x || place.y != y)
	{
		path.push_back(place);
		place = way[place.x][place.y];
	}
	path.push_back(place);
}
