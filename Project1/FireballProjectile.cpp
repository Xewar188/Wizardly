#include "FireballProjectile.h"
#include "Entity.h"
#include "Directions.h"

void FireballProjectile::addDeathAnimation()
{
	for (int i = 0; i < 20; i++)
	{
		RectangleShape toAdd = RectangleShape(Vector2f(80, 80));

		toAdd.setPosition((float)(getCenterX() - 40),
							(float)(getCenterY() - 40));
		toAdd.setFillColor(Color(255, i * 10, 0, 255 - i * 10));
		board->addObjectToAnimate(toAdd, i);

	}
}

FireballProjectile::FireballProjectile()
{
	state = 0.0f;
}
FireballProjectile::FireballProjectile(Entity a, Board& boarda)
{
	board = &boarda;
	type = a.getMode();
	damage = 40;
	Projectile::vela = 4 + a.getVel();
	Projectile::dir = a.getDirection();
	projectileId = boarda.nextId();
	switch (dir)
	{
	case UP:
		body = RectangleShape(Vector2f(14, 30));
		body.setPosition(a.getPosition().x + a.getSize().x / 2 - body.getSize().x / 2, 
							a.getPosition().y - body.getSize().y);
		toDraw.push_back(RectangleShape(Vector2f(10, 16)));
		break;
	case RIGHT:
		body = RectangleShape(Vector2f(30, 14));
		body.setPosition(a.getPosition().x + a.getSize().x,
							a.getPosition().y + a.getSize().y / 2 - body.getSize().y / 2);
		toDraw.push_back(RectangleShape(Vector2f(16, 10)));
		break;
	case DOWN:
		body = RectangleShape(Vector2f(14, 30));
		body.setPosition(a.getPosition().x + a.getSize().x / 2 - body.getSize().x / 2,
							a.getPosition().y + a.getSize().y);
		toDraw.push_back(RectangleShape(Vector2f(10, 16)));
		break;
	case LEFT:
		body = RectangleShape(Vector2f(30, 14));
		body.setPosition(a.getPosition().x - body.getSize().x,
							a.getPosition().y + a.getSize().y / 2 - body.getSize().y / 2);
		toDraw.push_back(RectangleShape(Vector2f(16, 10)));
		break;
	}

	body.setFillColor(Color(0, 0, 195));

	state = 0;
	toDraw[0].setFillColor(Color(0, 0, 195));
	toDraw.push_back(RectangleShape(Vector2f(6, 6)));
	toDraw[1].setFillColor(Color((int) (pow(sin(3.14159265358 / 8) * 255, 2)),
									(int) (pow(sin(3.14159265358 / 8) * 255, 2)),
									195));

	x = board->getCellX(getCenterX());
	y = board->getCellY(getCenterY());

	setAppearance();
	damage += a.getStrength() * 2;
}
bool FireballProjectile::move(int vel)
{
	if (age % 6 == 0)
		this->animate();
	age++;
	return Projectile::move(vel);
}



void FireballProjectile::hitWall()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board->getCell(x - 1 + i, y - 1 + j) != NULL)
				board->getCell(x - 1 + i, y - 1 + j)->hit(25);
	board->damageArea(FloatRect((float) getCenterX() - 40, (float)getCenterY() - 40, 80.0f, 80.0f), this);
	addDeathAnimation();
	
	this->remove();
}
bool FireballProjectile::hitEntity(Entity* toHit)
{

	if (toHit->getMode() * type <= 0)
	{
		this->remove();
		board->damageArea(FloatRect((float)getCenterX() - 40, (float)getCenterY() - 40, 80.0f, 80.0f), this);
		bool isEnd = false;
		addDeathAnimation();
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
		setAppearance();
		return false;
	}
}
void FireballProjectile::setAppearance()
{
	switch (dir)
	{
	case UP:
		toDraw[0].setPosition(body.getPosition().x + 2, 
								body.getPosition().y + 2);
		toDraw[1].setPosition(body.getPosition().x + 4, 
								body.getPosition().y + 4);
		break;
	case RIGHT:
		toDraw[0].setPosition(body.getPosition().x + body.getSize().x - toDraw[0].getSize().x - 2, 
								body.getPosition().y + 2);
		toDraw[1].setPosition(body.getPosition().x + body.getSize().x - toDraw[1].getSize().x - 4, 
								body.getPosition().y + 4);
		break;
	case DOWN:
		toDraw[0].setPosition(body.getPosition().x + 2, 
								body.getPosition().y + body.getSize().y - toDraw[0].getSize().y - 2);
		toDraw[1].setPosition(body.getPosition().x + 4, 
								body.getPosition().y + body.getSize().y - toDraw[1].getSize().y - 4);
		break;
	case LEFT:
		toDraw[0].setPosition(body.getPosition().x + 2,
								body.getPosition().y + 2);
		toDraw[1].setPosition(body.getPosition().x + 4, 
								body.getPosition().y + 4);
		break;
	}
}

void FireballProjectile::animate()
{
	state += (float)PI / 10;
	body.setFillColor(Color((int) (pow(sin(state - PI / 8), 2) * 255), 
							(int)(pow(sin(state - PI / 8), 2) * 255),
							195));

	toDraw[0].setFillColor(Color((int)(pow(sin(state), 2) * 255),
								(int)(pow(sin(state), 2) * 255),
									195));

	toDraw[1].setFillColor(Color((int)(pow(sin(state + PI / 8), 2) * 255),
								(int)(pow(sin(state + PI / 8), 2) * 255),
									195));
}