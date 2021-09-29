#include "BouncyProjectile.h"
#include "Entity.h"
#include "Directions.h"
BouncyProjectile::BouncyProjectile(Entity a, Board& boarda)
{
	projectileId = boarda.nextId();
	board = &boarda;
	dir = a.getDirection();
	type = a.getMode();
	body = RectangleShape(Vector2f(15, 15));
	vela = 4 + a.getVel();
	body.setFillColor(Color(85, 143, 41));

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

	damage = 13;
	damage += a.getStrength();
}
void BouncyProjectile::addDeathAnimation() {
	for (int i = 0; i < 10; i++)//dodawanie animacji
	{
		RectangleShape toAdd = RectangleShape(Vector2f(body.getSize().x * (10 - i) / 10,
			body.getSize().y * (10 - i) / 10));

		toAdd.setPosition(getCenterX() - toAdd.getSize().x / 2,
			getCenterY() - toAdd.getSize().y / 2);

		toAdd.setFillColor(Color(85, 143, 41));
		board->addObjectToAnimate(toAdd, i);

	}
}
bool BouncyProjectile::hitEntity(Entity* toHit)
{

	if (toHit->getMode() * type <= 0)
	{
		toHit->dealDamage(damage, this);
		addDeathAnimation();
		board->addProjectileToRemove(projectileId);

		return true;
	}
	else
	{
		switch (dir)
		{
		case UP:
			body.move(0, -1);
			break;
		case RIGHT:
			body.move(1, 0);
			break;
		case DOWN:
			body.move(0, 1);
			break;
		case LEFT:
			body.move(-1, 0);
			break;
		}
		return false;
	}
}
void BouncyProjectile::hitWall()
{
	if (bounceNr > 0)
	{
		bounceNr--;
		dir = reverseDirection(dir);
	}
	else
	{
		addDeathAnimation();
		board->addProjectileToRemove(projectileId);
	}
}
bool BouncyProjectile::move(int a)
{
	if (rand() % 150 == 0)
	{
		dir = turnClockwise(dir, rand());
	}
	return Projectile::move(a);
}