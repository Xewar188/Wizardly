#pragma once
#include "Projectile.h"

class Board;
class Entity;
class MagicBoltProjectile : public Projectile  //dodaj funkcje do usuwania , rysowania i poruszania pociskami do gameboard podczas tworzenia nowego pocisku
{
	int age = 0;
	float state = 0;//zmienne pomocnicze zwiazane z edycja wygladu
	void addDeathAnimation();
public:
	MagicBoltProjectile();
	MagicBoltProjectile(Entity c, Board& board);


	void hitWall();
	bool hitEntity(Entity* toHit);
	bool move(int vel = -1);
	void animate();
};