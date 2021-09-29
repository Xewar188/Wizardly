#include "ForcefieldProjectile.h"
#include "Entity.h"
#include <iostream>

ForcefieldProjectile::ForcefieldProjectile()
{

}
ForcefieldProjectile::ForcefieldProjectile(Entity a, Board& boarda, int pos, int end)
{
	projectileId = boarda.nextId();
	board = &boarda;
	type = a.getMode();
	dir = a.getDirection();
	vela = 8 + a.getVel();
	float width = std::max(board->getCellWidth() * 2, board->getCellHeight() * 2);
	switch (dir)
	{
	case 1:
		body = RectangleShape(Vector2f(width / end, 4));

		body.setPosition(a.getCenterX() - (width)/ 2 + width * pos / end + pos, 
							a.getPosition().y - body.getSize().y);


		toDraw.push_back(RectangleShape(Vector2f(width / end + 2, 4)));
		toDraw[0].setPosition(body.getPosition().x - 1, body.getPosition().y);
		break;
	case 2:
		body = RectangleShape(Vector2f(4, width / end));

		body.setPosition(a.getPosition().x + a.getSize().x, 
							a.getCenterY() + width * pos / end + pos - (width)/2);

		toDraw.push_back(RectangleShape(Vector2f(4, width / end + 2)));
		toDraw[0].setPosition(body.getPosition().x, body.getPosition().y - 1);
		break;
	case 3: 
		body = RectangleShape(Vector2f(width / end, 4));

		body.setPosition(a.getCenterX() + width * pos / end + pos - (width) / 2,
							a.getPosition().y + a.getSize().y);


		toDraw.push_back(RectangleShape(Vector2f(width / end + 2, 4)));
		toDraw[0].setPosition(body.getPosition().x - 1, body.getPosition().y);
		break;
	case 4:
		body = RectangleShape(Vector2f(4, width / end));

		body.setPosition(a.getPosition().x - body.getSize().x, 
							a.getCenterY() - (width) / 2 + width * pos / end + pos);

		toDraw.push_back(RectangleShape(Vector2f(4, width / end + 2)));
		toDraw[0].setPosition(body.getPosition().x, body.getPosition().y - 1);
		break;
	}
	x = board->getCellX(getCenterX());
	y = board->getCellY(getCenterY());
	toDraw[0].setFillColor(Color(138, 254, 255));
}
void ForcefieldProjectile::setAppearance()
{
	switch (dir)
	{
	case 1:
	case 3:
		toDraw[0].setPosition(body.getPosition().x - 1, body.getPosition().y);
		break;
	case 2:
	case 4:
		toDraw[0].setPosition(body.getPosition().x, body.getPosition().y - 1);
		break;


	}
}
void ForcefieldProjectile::draw(RenderTarget& window, RenderStates state) const
{
	window.draw(toDraw[0]);
}
void ForcefieldProjectile::hitWall()
{
	this->remove();
}
bool ForcefieldProjectile::hitEntity(Entity* toHit)
{
	float speed = 1;
	if (toHit->getMode() * type > 0)
	{
		return false;
	}
	if (toHit->move(this->dir, speed, 30))
	{
		return false;
	}
	else 
	{
		this->remove();
		return true;
	}
}