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
	float speed;
	bool isAgainstWall(Vector2i direction);
	bool tryMovingEntities(int forece, float& speed, Vector2i dir);
	void changeTile();
	void checkForMapChange();
protected:

	int randbase = 0;
	int vel = 2;
	RectangleShape body;
	std::vector<RectangleShape> toDraw;

	int weight=0;
	int strength=0;

	int attackSpeed = 0;
	Uint64 lastShot = 0;

	Weapon* weapon = NULL;
	int maxHealth;
	int health;
	RectangleShape healthBar;
	RectangleShape healthBarBackground;
	
	std::vector<Projectile*> personalProjectiles;
	std::vector<Projectile*> projectilesToRemove;
	std::vector<Vector2i> path;

	EntityType mode = NEUTRAL;
	int x, y;
	bool isTangible = true;
	bool interactable = false;
	Direction direction;
	bool movable = true;
	virtual void setAppearance();
public:
	Board* board;
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
	static float distance(Entity* e1, Entity* e2);
	virtual void findPath();
	virtual void draw(RenderTarget& window, RenderStates state) const;
	virtual bool move(int dir,float &speed,int force);
	virtual bool move(int dir, int force);
	virtual void onInteract(Player*cel);
	virtual void dealDamage(int dmg,Projectile* src=NULL);
	virtual void attack();
	virtual void setDir(int d);
	virtual void update();
	virtual void heal(int n);
	virtual void equipWeapon(Weapon* a);
};


