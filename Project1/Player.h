#pragma once
#include "Entity.h"

class Player :public Entity
{


	int artifactCounter = 0;
	int score = 0;
	int gold = 0;
	WeaponChart chart;
public:
	void giveGold(int value);
	void spendGold(int value);
	int getGold();

	void givePoints(int value);
	int getPoints();

	void increaseArtifactCounter();
	int getArtifactCounter();

	void unlockWeapon();

	Player();
	Player(float width, float height, float x, float y, Color color, Board* board);
	void interact();
	void dealDamage(int dmg, Projectile* src = NULL);
	void setAppearance();
	void nextWeapon();
	void previousWeapon();
	void equipWeapon(Weapon* a);

	void increaseHealth(int value);
	void increaseAttackSpeed(int value);

	void addPiece(RectangleShape toAdd);
	virtual void setVel(int vela);
	virtual void setStrength(int strengtha);

	void clearPlayer();
};