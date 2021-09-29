#pragma once
#include "Projectile.h"

class Board;
class Entity;
class ForcefieldProjectile : public Projectile
{
public:
	ForcefieldProjectile();
	ForcefieldProjectile(Entity a, Board& board, int pos, int i);
	void draw(sf::RenderTarget& window, sf::RenderStates state) const;
	void setAppearance();
	void hitWall();
	bool hitEntity(Entity* toHit);

};