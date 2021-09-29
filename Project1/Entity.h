#pragma once
#include "Board.h"
#include <SFML\Graphics.hpp>
#include "Settings.h"
#include <sstream>
#include "Projectile.h"
#include "WeaponChart.h"
enum Direction;
class Player;
enum EntityType { FRIEND = -1, NEUTRAL = 0, ENEMY = 1};
class Entity : public Drawable
{
	float speed;//zmienna pomocnicza potrzebna do poruszania
	bool isAgainstWall(Vector2i direction);
	bool tryMovingEntities(int forece, float& speed, Vector2i dir);
	void changeTile();
	void checkForMapChange();
protected:

	int randbase = 0;
	int vel = 2;//predkosc entity
	RectangleShape body;//glowne cialo 
	std::vector<RectangleShape> toDraw;//dodatkowe elementy wygladu

	//masa i sila sa zwiazane z poruszaniem sie i przesuwaniem innych objektow
	int weight=0;//masa
	int strength=0;//sila 

	int attackSpeed = 0;
	Uint64 lastShot = 0;// czas ostatniego ataku

	Weapon* weapon = NULL;//bron
	int maxHealth;//max zycie
	int health;//obecne zycie
	RectangleShape healthBar;//obecne zycie (pasek)
	RectangleShape healthBarBackground;//max zycie(pasek)
	
	std::vector<Projectile*> personalProjectiles;
	std::vector<Projectile*> projectilesToRemove;
	std::vector<Vector2i> path;

	EntityType mode = NEUTRAL;// 0- dla neutralnych(wszyscy zadaja im obrazenia a oni wszystkim) <0 dla przyjaznych(zadaja obrazenia wroga a nie przyjaznym(-1 zarezerwowane dla postaci gracza)) >0 dla postaci wrogich
	int x, y;//wspolzedne x,y obecnego kafelka
	bool isTangible = true;//czy entity wchodzi w kolizje z innymi
	bool interactable = false;//czy mozna przeprowadzac z nim interakcje
	Direction direction;//0 tylko dla movable=false
	bool movable = true;//czy mozna poruszyc
	virtual void setAppearance();//ustawienie i aktualizacja wygladu
public:
	Board* board;//plansza na ktorej sie znajduje
	Entity();
	~Entity();
	Entity(float width, float height, float x, float y, Color color,Color secondary,Board* board);
	bool equals(Entity* toCompare);
	void removePersonalProjectile(Projectile* toRemove);
	void setMapCoordinates();
	void remove();
	int getCenterX();
	int getCenterY();
	int getAttackSpeed();
	int getLastShootTime();
	void startCooldown();
	Direction getDirection();
	Vector2f getPosition();
	Vector2f getSize();
	int getMapCellX();
	int getMapCellY();
	int getMode();
	int getVel();
	int getStrength();
	FloatRect getBounds();
	bool isInteractable();
	bool isAlive();
	bool canBeInteracted();
	bool doesCollide();
	int getMaxHealth();
	int getHealth();
	void addProjectile(Projectile* p);
	static float distance(Entity* e1, Entity* e2);//obliczenie odleglosci miedzy 2 entity
	virtual void findPath();
	virtual void draw(RenderTarget& window, RenderStates state) const;
	virtual bool move(int dir,float &speed,int force);//rzeczywiste poruszenie entity(o jednen pixel)
	virtual bool move(int dir, int force);//poruszanie entity (o vel pixeli)
	virtual void onInteract(Player*cel);//podczas interakcji , cel to entity wywolujacy interakcje
	virtual void dealDamage(int dmg,Projectile* src=NULL);//zadawanie obrazen entity
	virtual void attack();//atak na mapie board
	virtual void setDir(int d);//ustawianie kierunku
	virtual void update();//czynnosci niezalezne od gracza
	virtual void heal(int n);//leczenie o ilosc n
	virtual void equipWeapon(Weapon* a);
};


