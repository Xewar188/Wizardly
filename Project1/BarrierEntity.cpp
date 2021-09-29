#include "BarrierEntity.h"
void BarrierEntity::createWideBody(int xLoc, int yLoc)
{
	int width = 0;
	int x = xLoc / (int) board->getCellWidth();
	int y = yLoc / (int) board->getCellHeight();
	int base = (int) std::max(board->getCellWidth(), board->getCellHeight());
	int offset = 0;
	if (!board->getCell(x, y)->isCellTangible())
	{
		width += (int) board->getCellWidth();
		offset = xLoc - (int)board->getCell(x, y)->getX();
	}
	if (x > 0 && !board->getCell(x - 1, y)->isCellTangible())
	{
		width += base - (int) (xLoc - board->getCell(x, y)->getX());
		offset = base;
	}
	if (x < COLUMNS_NUMBER - 1 && !board->getCell(x + 1, y)->isCellTangible())
	{
		width += base - (int) (board->getCell(x + 1, y)->getX() - xLoc);
	}
	body = RectangleShape(Vector2f((float) width, (float) 4));
	body.setPosition((float)(xLoc  - offset), (float)(yLoc - 2));
}
void BarrierEntity::createHighBody(int xLoc, int yLoc)
{
	int height = 0;
	int x = xLoc / (int) board->getCellWidth();
	int y = yLoc / (int) board->getCellHeight();
	int base = (int) std::max(board->getCellWidth(), board->getCellHeight());
	int offset = 0;
	if (!board->getCell(x, y)->isCellTangible())
	{
		height += (int) board->getCellHeight();
		offset = yLoc - (int) board->getCell(x, y)->getY();
	}
	if (y > 0 && !board->getCell(x, y - 1)->isCellTangible())
	{
		height += base - (int) (yLoc - board->getCell(x, y)->getY());
		offset = base;
	}
	if (y < ROWS_NUMBER - 1 && !board->getCell(x, y + 1)->isCellTangible())
	{
		height += base - (int) (board->getCell(x, y + 1)->getY() - yLoc);
	}
	body = RectangleShape(Vector2f(4.0f, (float) height));
	body.setPosition((float)(xLoc - 2), (float)(yLoc - offset));
}
BarrierEntity::BarrierEntity()
{
	age = 0;
	maxAge = 0;
}
BarrierEntity::BarrierEntity(Entity a, Board* boarda)
{
	board = boarda;
	float width = 0;
	movable = false;
	health = 150;
	mode = NEUTRAL;
	maxHealth = 150;
	interactable = true;
	age = 0;
	maxAge = 500;
	switch (a.getDirection())
	{
	case 1:

		createWideBody(a.getCenterX(), a.getCenterY() - (int) a.getSize().y / 2 - 35);
		break;
	case 2:
		createHighBody(a.getCenterX() + (int) a.getSize().x / 2 + 35, a.getCenterY());
		break;
	case 3:

		createWideBody(a.getCenterX(), a.getCenterY() + (int) a.getSize().y / 2 + 35);
		break;
	case 4:
		createHighBody(a.getCenterX() - (int)a.getSize().x / 2 - 35, a.getCenterY());
		break;
	}
	setMapCoordinates();
	body.setFillColor(Color(255, 255, 0));
	if (boarda->getCell(x, y)->isCellTangible())
	{
		age = maxAge;
	}

}
void BarrierEntity::update()
{
	Entity::update();
	age++;
	if (age > maxAge)
	{
		remove();
	}
}
void BarrierEntity::onInteract(Player* cel)
{
	remove();
}
void BarrierEntity::dealDamage(int dmg, Projectile* src)
{
	if (src != NULL)
		src->remove();
	health -= dmg;
	body.setFillColor(Color(255, 255, 0, (int)(255 * (float)health / (float)maxHealth)));
	if (health <= 0)
	{
		remove();
	}
}
