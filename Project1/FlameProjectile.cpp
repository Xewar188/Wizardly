#include "FlameProjectile.h"
#include "Entity.h"
#include "Directions.h"

FlameProjectile::FlameProjectile()
{
	range = 25;
	age = 0;
}
FlameProjectile::FlameProjectile(Entity a, Board& boarda)
{
	projectileId = boarda.nextId();
	board = &boarda;
	dir = a.getDirection();
	type = a.getMode();
	body = RectangleShape(Vector2f(10, 10));
	vela = 5;
	body.setFillColor(Color(255, 255, 0));
	switch (dir)
	{
	case UP:
		body.setPosition(a.getCenterX() - body.getSize().x / 2, 
							a.getPosition().y - body.getSize().y);
		break;
	case RIGHT:
		body.setPosition(a.getPosition().x + a.getSize().x,
							a.getCenterY() - body.getSize().y / 2);
		break;
	case DOWN:
		body.setPosition(a.getCenterX() - body.getSize().x / 2,
							a.getPosition().y + a.getSize().y);
		break;
	case LEFT:
		body.setPosition(a.getPosition().x - body.getSize().x, 
							a.getCenterY() - body.getSize().y / 2);
		break;
	}
	x = board->getCellX(getCenterX());
	y = board->getCellY(getCenterY());
	damage = 1;
	damage += a.getStrength() / 5;
}

void FlameProjectile::hitWall()
{
	this->remove();
}
bool FlameProjectile::hitEntity(Entity* toHit)
{
	if (age % 4 == 0 && toHit->getMode() * type <= 0)
		toHit->dealDamage(damage, this);
	return false;
}
void FlameProjectile::animate()
{

	body.setSize(Vector2f(body.getSize().x + 2, body.getSize().y + 2));
	body.move(-1, 0);
	body.move(0, -1);
	if (age % 7 == 0)
		body.setFillColor(Color(255, 255 - age * 10, 0));
	if (age > range)
	{
		age = 0;
		body.setSize(Vector2f(10, 10));
		body.move(25, 25);
	}

}
bool FlameProjectile::move(int vel)
{
	this->animate();

	age++;

	if (this->age >= this->range)
	{
		this->remove();
		return true;
	}
	return this->Projectile::move(vel);
}