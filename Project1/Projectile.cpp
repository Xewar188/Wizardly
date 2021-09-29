#include "pch.h"
#include <iostream>
#include "Board.h"
#include "Entity.h"
#include "Projectile.h"
#include "Directions.h"


void Projectile::draw(RenderTarget& window, RenderStates state) const
{
	
	window.draw(body, state);
	for (int i = 0; i < (int)toDraw.size(); i++)
		window.draw(toDraw[i], state);

}
bool Projectile::isOnMap() {
	int left = (int) body.getGlobalBounds().left;
	int top = (int) body.getGlobalBounds().top;
	int right = (int) body.getGlobalBounds().left + (int) body.getGlobalBounds().width;
	int bottom = (int) body.getGlobalBounds().top + (int) body.getGlobalBounds().height;
	return  left >= 0 && right < board->getWidth() && top >= 0 && bottom < board->getHeight();
}
bool Projectile::isInWall()
{
	int left = (int) body.getGlobalBounds().left;
	int top = (int) body.getGlobalBounds().top;
	int right = (int) body.getGlobalBounds().left + (int) body.getGlobalBounds().width;
	int bottom = (int) body.getGlobalBounds().top + (int) body.getGlobalBounds().height;
	return  !isOnMap() ||
			board->getCell(board->getCellX(left), board->getCellY(top))->isCellTangible() ||
			board->getCell(board->getCellX(left), board->getCellY(bottom))->isCellTangible() ||
			board->getCell(board->getCellX(right), board->getCellY(top))->isCellTangible() ||
			board->getCell(board->getCellX(right), board->getCellY(bottom))->isCellTangible();
}
Projectile::Projectile()
{
	projectileId = -1;
	board = NULL;
	damage = 0;
	vela = 0;
	dir = UP;
	x = 0;
	y = 0;
}
Projectile::Projectile(Entity a,Board &boarda)
{
	projectileId = -1;
	damage = 0;
	vela = 0;
	dir = UP;
	x = 0;
	y = 0;
	board = &boarda;

}
bool Projectile::equals(Projectile* toCompare)
{
	return projectileId == toCompare->projectileId;
}
int Projectile::getDamage()
{
	return damage;
}
int Projectile::getType()
{
	return type;
}
FloatRect Projectile::getGlobalBounds()
{
	return body.getGlobalBounds();
}
int Projectile::getCenterX()
{
	return (int) body.getPosition().x + (int) body.getSize().x/2;
}
int Projectile::getCenterY()
{
	return (int) body.getPosition().y + (int) body.getSize().y / 2;
}
bool Projectile::move(int vel)
{
	if (vel == -1)
	{
		vel = vela;
	}
	bool connects;
	
	for (int z = 0; z < vel; z++)
	{
		connects = false;
		Vector2i moveDir;
		switch (dir) {
		case UP:
			moveDir = Vector2i(0, -1);
			break;
		case RIGHT:
			moveDir = Vector2i(1, 0);
			break;
		case DOWN:
			moveDir = Vector2i(0, 1);
			break;
		case LEFT:
			moveDir = Vector2i(-1, 0);
			break;
		}
		body.move((float) moveDir.x, (float) moveDir.y);
		setAppearance();
		if (!isOnMap()) {
			this->remove();
			return true;
		}
		if (isInWall()) {
			this->hitWall();
			return true;
		}
		for (auto i = board->getEntityBeginPointer(); i != board->getEntityEndPointer(); i++)
		{
			if ((*i)->doesCollide())
				if (body.getGlobalBounds().intersects((*i)->getBounds()))
				{
					if (this->hitEntity(*i))
						return true;
				}
		}
		y = board->getCellY(getCenterY());
		x = board->getCellX(getCenterX());
	}
	return false;
}


void Projectile::remove()
{
	board->addProjectileToRemove(projectileId);
}