#pragma once
#include <SFML\Graphics.hpp>
#include "Settings.h"
#include <vector>	
#include <set>
#include "Cell.h"

using namespace sf;
class Entity;
class Projectile;
class MapTile;

class Board : public Drawable
{
	
	friend class GameController;

	
	Cell *board[COLUMNS_NUMBER][ROWS_NUMBER];
	float cellWidth, cellHeight;
	bool isTopOpen = false;
	bool isBottomOpen = false;
	bool isLeftOpen = false;
	bool isRightOpen = false;
	
	bool opener[4] = { 0,0,0,0 };
	bool toggle = false;
	
	int enemies = 0;
	int projectileIdCounter = 0;
	
	MapTile* map;
	Uint64 timer = 0;
	
	std::map<int, Projectile*> projectiles;
	std::set<int> projectilesToRemove;

	std::vector<Entity*> entity;
	std::vector<Entity*> entityToRemove;

	std::vector<std::vector<RectangleShape>> toAnimate;
	std::vector<std::vector<Text>> textToDraw;

public:
	static  std::vector<RectangleShape> playerSpeed;
	static  std::vector<RectangleShape> playerStrength;
	static Text playerSpeedText;
	static Text playerStrengthText;
	static  std::vector<RectangleShape> playerGold;
	static Text playerGoldText;

	void changeCell(int x, int y, Cell *toChange);
	
	void increaseEnemyCounter();
	void decreaseEnemyCounter();
	void addEntity(Entity* toAdd);
	void removeEntity(Entity* toRemove);
	std::vector<Entity*>::iterator getEntityBeginPointer();
	std::vector<Entity*>::iterator getEntityEndPointer();
	
	void addObjectToAnimate(RectangleShape toAdd, int howFarInFuture);
	void addTextToAnimate(Text toAdd, int howFarInFuture);
	void onInteract(Player* cel, int x, int y);
	void changeOpen(bool mode, int dir);
	Board();															
	Board(int mode,float width,float height);									
	~Board();
	void draw(RenderTarget& window, RenderStates state) const;
	
	float getCellWidth();
	float getCellHeight();
	int getCellX(int x);
	int getCellY(int y);
	Cell *getCell(int x, int y);

	Uint64 getTime();

	int getWidth();
	int getHeight();

	MapTile* getMap();
	
	void addProjectileToRemove(int id);
	void addProjectile(int id, Projectile* toAdd);
	std::map<int, Projectile*>::iterator getProjectileBeginPointer();
	std::map<int, Projectile*>::iterator getProjectileEndPointer();

	void update();

	bool isSideOpen(int side);
	bool canSideBeOpened(int side);

	int nextId();
	int currentId();

	void damageArea(FloatRect shape, Projectile* src);

	void clearBoard();
};



