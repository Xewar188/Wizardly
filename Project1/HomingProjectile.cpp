#include "HomingProjectile.h"
#include "Entity.h"
#include "Directions.h"
HomingProjectile::HomingProjectile(Entity& a, Board& boarda)
{
	projectileId = boarda.nextId();
	board = &boarda;
	dir = a.getDirection();
	type = a.getMode();
	body = RectangleShape(Vector2f(12, 12));
	vela = 5 + a.getVel();
	body.setFillColor(Color(200, 0, 0));
	switch (dir)
	{
	case 1:
		body.setPosition(a.getCenterX() - body.getSize().x / 2, 
							a.getPosition().y - body.getSize().y);
		break;
	case 2:
		body.setPosition(a.getPosition().x + a.getSize().x,
							a.getCenterY() - body.getSize().y / 2);
		break;
	case 3:
		body.setPosition(a.getCenterX() - body.getSize().x / 2,
							a.getPosition().y + a.getSize().y);
		break;
	case 4:
		body.setPosition(a.getPosition().x - body.getSize().x, 
							a.getCenterY() - body.getSize().y / 2);
		break;
	}
	toDraw.push_back(RectangleShape(Vector2f(8, 8)));
	toDraw[0].setFillColor(Color(160, 0, 0));
	x = board->getCellX(getCenterX());
	y = board->getCellY(getCenterY());
	float minDis = 100000;
	target = NULL;

	damage = 20;
	damage += a.getStrength();
	setAppearance();
}
void HomingProjectile::hitWall()
{
	this->remove();
}
bool HomingProjectile::hitEntity(Entity* toHit)
{
	if (toHit->getMode() * type <= 0)
	{
		toHit->dealDamage(damage);
		this->remove();
		return true;
	}
	return false;
}
void HomingProjectile::setAppearance()
{
	toDraw[0].setPosition(getCenterX() - toDraw[0].getSize().x / 2, 
							getCenterY() - toDraw[0].getSize().y / 2);
}
bool HomingProjectile::move(int vel)
{
	if (vel == -1)
		vel = vela;
	Vector2f dis;
	Vector2f minDis = Vector2f(10000, 10000);
	bool pass = false;
	for (int i = 0; i < vel; i++)
	{
		target = NULL;
		for (auto i = board->getEntityBeginPointer(); i != board->getEntityEndPointer(); i++)
		{
			switch (dir)
			{
			case 1:
				pass = (getCenterY() >= (*i)->getCenterY());
				break;
			case 2:
				pass = (getCenterX() <= (*i)->getCenterX());
				break;
			case 3:
				pass = (getCenterY() <= (*i)->getCenterY());
				break;
			case 4:
				pass = (getCenterX() >= (*i)->getCenterX());
				break;
			}

			if (pass)
				if ((*i)->getMode() * type < 0)
				{
					dis = Vector2f((float) getCenterX() - (*i)->getCenterX(),
									(float) getCenterY() - (*i)->getCenterY());
					if (dis.x * dis.x + dis.y * dis.y < minDis.x * minDis.x + minDis.y * minDis.y)
					{
						target = (*i);
						minDis = dis;
					}
				}
		}

		if (target == NULL)
		{
			if (Projectile::move(1))
				break;
		}
		else
			if ((dir == 1 && target->getCenterY() + 1 < getCenterY())
				|| (dir == 2 && target->getCenterX() > getCenterX() + 1)
				|| (dir == 3 && target->getCenterY() > getCenterY() + 1)
				|| (dir == 4 && target->getCenterX() + 1 < getCenterX()))
			{
				if (Projectile::move(1))
					break;
			}
			else
			{

				if (target->getCenterY() < getCenterY() && dir != 1)
				{
					dir = UP;
					if (Projectile::move(1))
						break;
					continue;
				}
				if (target->getCenterX() > getCenterX() && dir != 2)
				{
					dir = RIGHT;
					if (Projectile::move(1))
						break;
					continue;
				}
				if (target->getCenterY() > getCenterY() && dir != 3)
				{
					dir = DOWN;
					if (Projectile::move(1))
						break;
					continue;
				}
				if (target->getCenterX() < getCenterX() && dir != 4)
				{
					dir = LEFT;
					if (Projectile::move(1))
						break;
					continue;
				}
				
			}
	}
	return false;
}