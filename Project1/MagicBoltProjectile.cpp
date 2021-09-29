#include "MagicBoltProjectile.h"
#include "Entity.h"

MagicBoltProjectile::MagicBoltProjectile()
{

}
MagicBoltProjectile::MagicBoltProjectile(Entity a, Board& boarda)
{
	board = &boarda;
	dir = a.getDirection();
	type = a.getMode();
	body = sf::RectangleShape(Vector2f(10, 10));
	vela = 1 + a.getVel();
	body.setFillColor(Color(102, 0, 204));
	projectileId = boarda.nextId();
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
	x = board->getCellX(getCenterX());
	y = board->getCellY(getCenterY());
	damage = 15;
	damage += a.getStrength();
}

void MagicBoltProjectile::addDeathAnimation() {

	for (int i = 0; i < 7; i++)
	{
		RectangleShape toAdd = RectangleShape(Vector2f(10.0f - i * 5 / 7, 10.0f - i * 5 / 7));
		toAdd.setPosition((float) getCenterX() - toAdd.getSize().x / 2,
							(float) getCenterY() - toAdd.getSize().y / 2);
		toAdd.setFillColor(Color::White);
		board->addObjectToAnimate(toAdd, i);

	}
}
bool MagicBoltProjectile::hitEntity(Entity* toHit)
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
		case 1:
			body.move(0, -1);
			break;
		case 2:
			body.move(1, 0);
			break;
		case 3:
			body.move(0, 1);
			break;
		case 4:
			body.move(-1, 0);
			break;
		}
		return false;
	}
}
void MagicBoltProjectile::hitWall()
{
	addDeathAnimation();
	board->getCell(x, y)->hit(1);
	if(board->getCell(x - ((dir + 1) % 2) * (dir - 3), y + (dir % 2) * (dir - 2)) != NULL)
		board->getCell(x - ((dir + 1) % 2) * (dir - 3) , y + (dir % 2) * (dir - 2))->hit(1);
	board->addProjectileToRemove(projectileId);
}

bool MagicBoltProjectile::move(int vel)
{
	if (age % 8 == 0)
		animate();
	age++;
	return Projectile::move(vel);
}
void MagicBoltProjectile::animate()
{
	state += PI / 5;
	body.setFillColor(Color(147 - (int)(45 * cos(state)), 0, 204));

}