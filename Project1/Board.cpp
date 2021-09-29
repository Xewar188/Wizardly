#include "Board.h"
#include "Map.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include "Player.h"
#include "Chest.h"
#include "Warrior.h"
#include "Vendor.h"
#include "Artifact.h"
#include "Mage.h"
#include "StartTile.h"
#include "Projectile.h"
#include "Healpoint.h"
#include "HealthVendor.h"
#include "AttackSpeedVendor.h"
#include "Wall.h"
#include "Plains.h"
#include "Stone.h"
#include "SpeedShrine.h"
#include "UsedShrine.h"
#include "GameController.h"

Board::Board()
{
	map = NULL;
	for (int i = 0; i < COLUMNS_NUMBER; i++)
		for (int j = 0; j < ROWS_NUMBER; j++)
			board[i][j] = NULL;
	Board::cellHeight = 0;
	Board::cellWidth = 0;
	map = NULL;
}
Board::Board(int mode, float width, float height)
{
	map = NULL;
	for (int i = 0; i < COLUMNS_NUMBER; i++)
		for (int j = 0; j < ROWS_NUMBER; j++)
			board[i][j] = NULL;
	Board::cellHeight = height / ROWS_NUMBER;
	Board::cellWidth = width / COLUMNS_NUMBER;
	toggle = false;
}

Board::~Board()
{

	for (int i = 0; i < COLUMNS_NUMBER; i++)
		for (int j = 0; j < ROWS_NUMBER; j++)
			if (board[i][j] != NULL) {
				delete board[i][j];
			}
}
Cell* Board::getCell(int x, int y)
{
	if (x < COLUMNS_NUMBER && x >= 0 && y >= 0 && y < ROWS_NUMBER)
		return board[x][y];
	else
		return NULL;
		
}
Uint64 Board::getTime()
{
	return timer;
}
int Board::getHeight()
{
	return ((int)cellHeight) * ROWS_NUMBER;
}
MapTile* Board::getMap()
{
	return map;
}
void Board::addProjectileToRemove(int id)
{
	projectilesToRemove.insert(id);
}
void Board::addProjectile(int id, Projectile* toAdd)
{
	projectiles.emplace(id, toAdd);
}
std::map<int, Projectile*>::iterator Board::getProjectileBeginPointer()
{
	return projectiles.begin();
}
std::map<int, Projectile*>::iterator Board::getProjectileEndPointer()
{
	return projectiles.end();
}
int Board::getWidth()
{
	return ((int)cellWidth) * COLUMNS_NUMBER;
}

void Board::changeOpen(bool mode, int dir)
{
	int startX = 0, startY = 0;
	int xMod = 0, yMod = 0;
	switch (dir)
	{
	case 1:						//top
		isTopOpen = mode;
		xMod = 1;
		startX = COLUMNS_NUMBER / 2 - 1;
		break;
	case 2:							//right
		isRightOpen = mode;
		yMod = 1;
		startX = COLUMNS_NUMBER - 1;
		startY = ROWS_NUMBER / 2 - 1;
		break;
	case 3:							//bottom
		isBottomOpen = mode;
		xMod = 1;
		startX = COLUMNS_NUMBER / 2 - 1;
		startY = ROWS_NUMBER - 1;
		break;
	case 4:							//left
		isLeftOpen = mode;
		yMod = 1;
		startX = 0;
		startY = ROWS_NUMBER / 2 - 1;
	}
	if (!mode)
	{
		for (int i = 0; i < 3; i++)
		{
			changeCell(startX + xMod * i, startY + yMod * i,
				new Wall(this, startX + xMod * i, startY + yMod * i));
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			changeCell(startX + xMod * i, startY + yMod * i, 
				new Plains(this, startX + xMod * i, startY + yMod * i));
		}
	}
}

void Board::changeCell(int x, int y, Cell* toChange)
{
	delete board[x][y];
	board[x][y] = toChange;
}

void Board::increaseEnemyCounter()
{
	enemies++;
}

void Board::decreaseEnemyCounter()
{
	enemies--;
}

void Board::addEntity(Entity* toAdd)
{
	entity.push_back(toAdd);
}

void Board::draw(RenderTarget& window, RenderStates state) const
{	
	for (int i = 0; i < COLUMNS_NUMBER; i++)
		for (int j = 0; j < ROWS_NUMBER; j++)
			window.draw(*board[i][j]);
		
		

	for (int i = (int)entity.size() - 1; i >= 0; i--)//postacie
	{
		window.draw(*entity[i]);

	}
	for (auto i = projectiles.begin(); i !=projectiles.end() ; i++)//pociski wszystkich rodzajow
		window.draw(*i->second);
		
	if(toAnimate.size() > 0)
		for (int i = 0; i < (int)toAnimate[0].size(); i++)
		{
			window.draw(toAnimate[0][i], state);
		}
		
	if (textToDraw.size() > 0)
	{
		for (int i = 0; i < (int)textToDraw[0].size(); i++)
		{
			window.draw(textToDraw[0][i], state);
		}
	}
		
};
	
void Board::removeEntity(Entity *toRemove)
{
	board[toRemove->getMapCellX()][toRemove->getMapCellY()]->setFilled(false);
			entityToRemove.push_back(toRemove);
}

std::vector<Entity*>::iterator Board::getEntityBeginPointer()
{
	return entity.begin();
}

std::vector<Entity*>::iterator Board::getEntityEndPointer()
{
	return entity.end();
}

void Board::addObjectToAnimate(RectangleShape toAdd, int howFarInFuture)
{
	while ((int) toAnimate.size() <= howFarInFuture) {
		toAnimate.push_back(std::vector<RectangleShape>());
	}
		toAnimate[howFarInFuture].push_back(toAdd);
}

void Board::addTextToAnimate(Text toAdd, int howFarInFuture)
{
	while ((int)textToDraw.size() <= howFarInFuture) {
		textToDraw.push_back(std::vector<Text>());
	}
	textToDraw[howFarInFuture].push_back(toAdd);
}
float Board::getCellHeight()
{
	return cellHeight;
}
int Board::getCellX(int x)
{
	return (int) (x / getCellWidth());
}
int Board::getCellY(int y)
{
	return (int) (y / getCellHeight());
}
float Board::getCellWidth()
{
	return cellWidth;
}
void Board::onInteract(Player* cel, int x, int y)
{
	board[x][y]->onInteract(cel);
}

void Board::update()
{
		
	if (enemies > 0
		&& GameController::getPlayer()->getMapCellX() > 0
		&& GameController::getPlayer()->getMapCellX() < COLUMNS_NUMBER - 1
		&& GameController::getPlayer()->getMapCellY() > 0
		&& GameController::getPlayer()->getMapCellY() < ROWS_NUMBER - 1)
	{
		for (int i = 0; i < 4; i++)
			changeOpen(false, i + 1);
	}
	if (enemies == 0 && !toggle)
	{
			
		toggle = true;
		for (int i = 0; i < 4; i++)
			changeOpen(opener[i], i + 1);
	}
	if (toAnimate.size() > 0)
	{
		toAnimate.erase(toAnimate.begin());
	}
	if (textToDraw.size() > 0)
	{
		textToDraw.erase(textToDraw.begin());
	}
	for (int i = 0; i < COLUMNS_NUMBER; i++)
		for (int j = 0; j < ROWS_NUMBER; j++)
			board[i][j]->update();
	for (int i = 0; i < (int)entity.size(); i++)
	{	
		entity[i]->update();
	}
		
	for (auto i = projectiles.begin(); i != projectiles.end(); i++)
	{
		i->second->move();
	}
	if (projectilesToRemove.size() != 0)
	{
		int help;
		std::set<int>::iterator last = projectilesToRemove.empty() ? projectilesToRemove.end() : std::prev(projectilesToRemove.end());
		for (int i = 0; i < (int)projectilesToRemove.size(); i++)
		{

				
			help = *last;
			delete (projectiles[help]);
			for (auto i = projectiles.begin(); i != projectiles.end(); i++)
			{
				if (i->first == *last)
				{
					projectiles.erase(i);
					break;
				}
			}
				
			last--;
				
		}
	}
	projectilesToRemove.clear();

	for (Entity* en : entityToRemove) {
		for (auto i = entity.begin(); i != entity.end(); i++) {
			if ((*i)->equals(en)) {
				entity.erase(i);
				delete en;
				break;
			}
		}
	}
	entityToRemove.clear();

	timer++;
		
}

bool Board::isSideOpen(int side)
{
	switch (side) {
	case 1:
		return isTopOpen;
	case 2:
		return isRightOpen;
	case 3:
		return isBottomOpen;
	case 4:
		return isLeftOpen;
	}
	return false;
}

bool Board::canSideBeOpened(int side)
{
	return opener[side % 4];
}

int Board::nextId()
{
	return ++projectileIdCounter;
}

int Board::currentId()
{
	return projectileIdCounter;
}

void Board::damageArea(FloatRect shape, Projectile *src)
{
	for (int i = 0; i < (int) entity.size(); i++)
	{
		if (entity[i]->getMode() * src->getType() <= 0)
			if (shape.intersects(entity[i]->getBounds()))
				entity[i]->dealDamage(src->getDamage(), src);

	}
}

void Board::clearBoard()
{
	for (int i = 0; i < COLUMNS_NUMBER; i++)
		for (int j = 0; j < ROWS_NUMBER; j++)
			if (board[i][j] != NULL) {
				delete board[i][j];
			}
	for (int i = 0; i < (int)entity.size(); i++)
	{
		if (entity[i] == GameController::getPlayer())
			continue;
		delete entity[i];
	}
	for (int i = 0; i < (int)projectiles.size(); i++)
	{
		delete projectiles[i];
	}
	entity.clear();
	projectiles.clear();
	toAnimate.clear();
	textToDraw.clear();
		
}


	