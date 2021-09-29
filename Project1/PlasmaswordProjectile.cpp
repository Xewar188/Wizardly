#include "PlasmaswordProjectile.h"
#include "Entity.h"

void PlasmaswordProjectile::setAppearance()
{

	switch (dir)
	{
	case 1:
		toDraw[0].setPosition(src->getPosition().x + src->getSize().x - 5,
			src->getPosition().y + 5);
		break;
	case 2:
		toDraw[0].setPosition(src->getPosition().x + src->getSize().x - 5,
			src->getPosition().y + src->getSize().y - 5);
		break;
	case 3:
		toDraw[0].setPosition(src->getPosition().x + 5,
			src->getPosition().y + src->getSize().y - 5);
		break;
	case 4:
		toDraw[0].setPosition(src->getPosition().x + 5,
			src->getPosition().y + 5);
		break;
	}
}

PlasmaswordProjectile::PlasmaswordProjectile()
{
	angleorg = 0;
	src = NULL;
}
PlasmaswordProjectile::PlasmaswordProjectile(Entity* a, Board& boarda, Color c)
{
	projectileId = boarda.nextId();
	board = &boarda;
	src = a;
	toDraw.push_back(RectangleShape(Vector2f(40, 5)));
	angleorg = 0;
	switch (src->getDirection())
	{
	case 1:
		toDraw[0].setRotation(340);
		angleorg = 340;
		break;
	case 2:
		toDraw[0].setRotation(70);
		angleorg = 70;
		break;
	case 3:
		toDraw[0].setRotation(160);
		angleorg = 160;
		break;
	case 4:
		toDraw[0].setRotation(250);
		angleorg = 250;
		break;
	}
	setAppearance();
	toDraw[0].setFillColor(c);
	dir = src->getDirection();
}
bool PlasmaswordProjectile::move(int vel)
{

	if (angle < -120)
	{
		this->remove();
	}
	if (src != NULL)
	{
		angle -= 15;
		toDraw[0].setRotation(angleorg + angle);
		setAppearance();
		FloatRect areaToRemove;
		switch (src->getDirection())
		{
		case 1:
			areaToRemove = FloatRect((float) src->getCenterX() - 20, (float) src->getCenterY() - 40 - src->getSize().y / 2, 40.0f, 40.0f);
			break;
		case 2:
			areaToRemove = FloatRect((float) src->getCenterX() + src->getSize().x / 2, (float) src->getCenterY() - 20, 40.0f, 40.0f);
			break;
		case 3:
			areaToRemove = FloatRect((float)  src->getCenterX() - 20, (float) src->getCenterY() + src->getSize().y / 2, 40.0f, 40.0f);
			break;
		case 4:
			areaToRemove = FloatRect((float) src->getCenterX() - 40 - src->getSize().x / 2, (float) src->getCenterY() - 20, 40.0f, 40.0f);
			break;
		}
		for (auto i = board->getProjectileBeginPointer(); i != board->getProjectileEndPointer(); i++)
		{
			if (i->second->getType() * src->getMode() <= 0)
				if (areaToRemove.intersects(i->second->getGlobalBounds()))
					i->second->remove();

		}
		src->setDir(dir);
	}
	else
	{
		this->remove();
	}
	return false;
}
void PlasmaswordProjectile::remove()
{
	src->removePersonalProjectile(this);
}