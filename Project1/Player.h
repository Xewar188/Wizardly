#pragma once
#include "Entity.h"

class Player :public Entity
{


	int artifactCounter = 0;
	int score = 0;
	int gold = 0;
	WeaponChart chart;//obiekt zawierajacy bronie
public:
	void giveGold(int value);
	void spendGold(int value);
	int getGold();

	void givePoints(int value);
	int getPoints();

	void increaseArtifactCounter();
	int getArtifactCounter();

	void unlockWeapon();

	Player();//mode - -1
	Player(float width, float height, float x, float y, Color color, Board* board);
	void interact();//interakcja z mapa, innym entity
	void dealDamage(int dmg, Projectile* src = NULL);
	void setAppearance();
	void nextWeapon();//zmiana broni na nastepna
	void previousWeapon();//zmiana broni na poprzednia
	void equipWeapon(Weapon* a);

	void increaseHealth(int value);
	void increaseAttackSpeed(int value);

	void addPiece(RectangleShape toAdd);
	virtual void setVel(int vela);
	virtual void setStrength(int strengtha);

	void clearPlayer();
};