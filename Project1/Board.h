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

	
	Cell *board[COLUMNS_NUMBER][ROWS_NUMBER];//przechowanie wyrzystkich danych potrzebnych do obliczen
	float cellWidth, cellHeight;//szerokosc i wysokosc kazdej komorki
	bool isTopOpen = false;//czy wyjscie od odpowiedniej strony istnieje
	bool isBottomOpen = false;
	bool isLeftOpen = false;
	bool isRightOpen = false;
	
	bool opener[4] = { 0,0,0,0 };
	bool toggle = false;
	
	int enemies = 0;
	int projectileIdCounter = 0;
	
	MapTile* map;// wskaznik do mapy poloczonej z ta plansza
	Uint64 timer = 0;//liczenie czasu(potrzebne do kalkulowania cooldownow)
	
	std::map<int, Projectile*> projectiles;//wszystkie pociski
	std::set<int> projectilesToRemove;//pomocniczy wektor przechowujacy wszystkie pociski do usuniecia w danej iteracji

	std::vector<Entity*> entity;//wszystkie entity
	std::vector<Entity*> entityToRemove;

	std::vector<std::vector<RectangleShape>> toAnimate;//animacje odtwarzane na planszy kazdy vector to osobna klatka
	std::vector<std::vector<Text>> textToDraw;

public:
	static  std::vector<RectangleShape> playerSpeed;
	static  std::vector<RectangleShape> playerStrength;
	static Text playerSpeedText;
	static Text playerStrengthText;
	static  std::vector<RectangleShape> playerGold;
	static Text playerGoldText;

	void changeCell(int x, int y, Cell *toChange);// zmiana typu komorki o wspolrzednych w board[x][y]
	
	void increaseEnemyCounter();
	void decreaseEnemyCounter();
	void addEntity(Entity* toAdd);
	void removeEntity(Entity* toRemove);//usuniecie entity z planszy
	std::vector<Entity*>::iterator getEntityBeginPointer();
	std::vector<Entity*>::iterator getEntityEndPointer();
	
	void addObjectToAnimate(RectangleShape toAdd, int howFarInFuture);
	void addTextToAnimate(Text toAdd, int howFarInFuture);
	void onInteract(Player* cel, int x, int y);
	//stworzenie mapy na podstawie danych zawartych w board //1
	void changeOpen(bool mode, int dir);//zmiana otwarcia kazdego z kierunkow mapy	
	Board();															//4     dir       2
	Board(int mode,float width,float height);									//3
	~Board();
	void draw(RenderTarget& window, RenderStates state) const;
	
	float getCellWidth();//zwraca szerokosc komorki
	float getCellHeight();//zwraca wysokosc komorki
	int getCellX(int x);
	int getCellY(int y);
	Cell *getCell(int x, int y);//zwraca dana komorke

	Uint64 getTime();

	int getWidth();
	int getHeight();

	MapTile* getMap();
	
	void addProjectileToRemove(int id);
	void addProjectile(int id, Projectile* toAdd);
	std::map<int, Projectile*>::iterator getProjectileBeginPointer();
	std::map<int, Projectile*>::iterator getProjectileEndPointer();

	void update();// updateuje mape(wykonuje operacjie niezalezne od gracza)

	bool isSideOpen(int side);
	bool canSideBeOpened(int side);

	int nextId();
	int currentId();

	void damageArea(FloatRect shape, Projectile* src);

	void clearBoard();
};



