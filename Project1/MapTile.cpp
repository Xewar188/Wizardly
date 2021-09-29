#include "MapTile.h"
#include "Board.h"
#include "Settings.h"
#include "Directions.h"
MapTile::MapTile(Board& board, sf::Vector2u windowSize)
{
	boarda = &board;
	veil = sf::RectangleShape(sf::Vector2f((float) windowSize.x / MAP_DIVISION, 
											(float) windowSize.y / MAP_DIVISION));
	veil.setFillColor(sf::Color(160, 170, 187));
	toDraw.push_back(sf::RectangleShape(sf::Vector2f((float)windowSize.x / MAP_DIVISION,
														(float)	windowSize.y / MAP_DIVISION)));
	toDraw[0].setFillColor(sf::Color(37, 89, 0));

	toDraw.push_back(sf::RectangleShape(sf::Vector2f((float) windowSize.x / MAP_DIVISION / 6 * 5, 
														(float) windowSize.y / MAP_DIVISION / 3 * 2)));
	toDraw[1].setFillColor(sf::Color(51, 204, 51));
	
	float height = toDraw[1].getSize().y;
	if (board.isSideOpen(UP))
		height += (toDraw[0].getSize().y - toDraw[1].getSize().y) / 2;
	if (board.isSideOpen(DOWN))
		height += (toDraw[0].getSize().y - toDraw[1].getSize().y) / 2;
	toDraw.push_back(sf::RectangleShape(sf::Vector2f((float) windowSize.x / 6 / MAP_DIVISION, height)));
	toDraw[2].setFillColor(Color(51, 204, 51));

	float width = toDraw[1].getSize().x;
	if (board.isSideOpen(LEFT))
		width += (toDraw[0].getSize().x - toDraw[1].getSize().x) / 2;
	if (board.isSideOpen(RIGHT))
		width += (toDraw[0].getSize().x - toDraw[1].getSize().x) / 2;
	toDraw.push_back(RectangleShape(Vector2f(width, (float) windowSize.y / MAP_DIVISION / 3)));
	toDraw[3].setFillColor(Color(51, 204, 51));

	setAppearance();
}

void setShapeArrayPosition(std::vector<RectangleShape> &shapes, int center, int y, int breakSize) {
	for (size_t i = 0; i < shapes.size(); i++)
	{
		shapes[i].setPosition(center
			- shapes[i].getSize().x * shapes.size() / 2 - breakSize * (shapes.size() - 1) / 2
			+ i * shapes[i].getSize().x + i * breakSize,
			y - shapes[0].getSize().y / 2);
	}
}

void MapTile::setAppearance()
{
	veil.setPosition(x, y);
	toDraw[0].setPosition(x, y);
	toDraw[1].setPosition(x + (toDraw[0].getSize().x - toDraw[1].getSize().x) / 2, 
							y + (toDraw[0].getSize().y - toDraw[1].getSize().y) / 2);
	float temp = 0;
	if (!boarda->canSideBeOpened(0))
		temp += (toDraw[0].getSize().y - toDraw[1].getSize().y) / 2;
	toDraw[2].setPosition(x + toDraw[0].getSize().x / 2 - toDraw[2].getSize().x / 2, y + temp);

	temp = 0;
	if (!boarda->canSideBeOpened(3))
		temp += (toDraw[0].getSize().x - toDraw[1].getSize().x) / 2;
	toDraw[3].setPosition(x + temp, y + toDraw[0].getSize().y / 2 - toDraw[3].getSize().y / 2);

	int emptyLength = 10;
	setShapeArrayPosition(chestsShape, (int) x + (int)toDraw[0].getSize().x / 2,
		(int) y + (int) toDraw[0].getSize().y / 2, emptyLength);
	setShapeArrayPosition(chestsTopShape, (int) x + (int)toDraw[0].getSize().x / 2,
		(int) y + (int) toDraw[0].getSize().y / 2, emptyLength + 6);
	int offset;

	if (chestsShape.size() > 0)
		offset = (int) chestsShape[0].getSize().y;
	else
		offset = 0;

	setShapeArrayPosition(healShape, (int) x + (int) toDraw[0].getSize().x / 2,
		(int) y + (int) toDraw[0].getSize().y / 2 - 10 - offset, emptyLength);
	
	if (isShrine)
		offset = 60 - (int) shrineShape.getSize().y;
	else
		offset = 0;
	
	if (vendors > 0)
	setShapeArrayPosition(vendorShape, (int) x + (int) toDraw[0].getSize().x / 2,
		(int) y + (int) toDraw[0].getSize().y / 2 + 10 + offset + 2 * (int) vendorShape[0].getSize().y, emptyLength);
	if (isShrine)
	{
		shrineShape.setPosition(x + toDraw[0].getSize().x / 2 - shrineShape.getSize().x / 2,
								y + toDraw[0].getSize().y / 2 - shrineShape.getSize().y / 2 + 40);
	}
}
void MapTile::draw(RenderTarget& window, RenderStates state) const
{
	if (found)
	{
		for (size_t i = 0; i < toDraw.size(); i++)
			window.draw(toDraw[i]);
		for (size_t i = 0; i < chestsShape.size(); i++)
		{
			window.draw(chestsShape[i]);
		}
		for (size_t i = 0; i < chestsTopShape.size(); i++)
		{
			window.draw(chestsTopShape[i]);
		}

		for (size_t i = 0; i < healShape.size(); i++)
		{
			window.draw(healShape[i]);
		}
		for (size_t i = 0; i < vendorShape.size(); i++)
		{
			window.draw(vendorShape[i]);
		}
		if (isShrine)
		{
			window.draw(shrineShape);
		}
	}
	else
	{
		window.draw(veil);
	}

}
void MapTile::update()
{
	chestsShape.clear();
	chestsTopShape.clear();
	healShape.clear();
	vendorShape.clear();
	for (int i = 0; i < chests; i++)
	{
		chestsShape.push_back(RectangleShape(Vector2f(20, 20)));
		chestsShape[chestsShape.size() - 1].setFillColor(Color(176, 46, 0));
		chestsTopShape.push_back(RectangleShape(Vector2f(14, 14)));
		chestsTopShape[chestsShape.size() - 1].setFillColor(Color(255, 204, 0));
	}
	for (int i = 0; i < healing; i++)
	{
		healShape.push_back(RectangleShape(Vector2f(15, 15)));
		healShape[healShape.size() - 1].setFillColor(Color::Red);
	}
	for (int i = 0; i < vendors; i++)
	{
		vendorShape.push_back(RectangleShape(Vector2f(20, 20)));
		vendorShape[vendorShape.size() - 1].setFillColor(Color(255, 225, 0));
	}
	if (isShrine)
	{
		if (shrineType < 3)
			shrineShape = RectangleShape(Vector2f(25, 25));
		else
			shrineShape = RectangleShape(Vector2f(30, 30));
		switch (shrineType)
		{
		case 1:
			shrineShape.setFillColor(Color(0, 102, 204));
			break;
		case 2:
			shrineShape.setFillColor(Color(0, 153, 51));
			break;
		case 3:
			shrineShape.setFillColor(Color::White);
			break;
		case 5:
			shrineShape.setFillColor(Color::Black);
			break;

		}
	}
	setAppearance();
}
void MapTile::useShrine() {
	isShrine = false;
	shrineType = -1;
}
void MapTile::setShrine(int type) {
	isShrine = true;
	shrineType = type;
}

bool MapTile::hasShrine()
{
	return isShrine;
}

void MapTile::find()
{
	found = true;
}

void MapTile::addHealing(int i) {
	healing += i;
}
int MapTile::healingLeft() {
	return healing;
}
void MapTile::useHealing() {
	healing--;
}
void MapTile::addChest() {
	chests++;
}
void MapTile::useChest() {
	chests--;
}
void MapTile::addVendor() {
	vendors++;
}

void MapTile::useVendor()
{
	vendors--;
}

void MapTile::setMainStatus()
{
	toDraw[0].setFillColor(sf::Color(5, 81, 0));
}

void MapTile::removeMainStatus()
{
	toDraw[0].setFillColor(sf::Color(37, 89, 0));
}

void MapTile::setLocationX(int x)
{
	this->x = (float) x;
}

void MapTile::setLocationY(int y)
{
	this->y = (float) y;
}

void MapTile::changeLocationX(int delta)
{
	this->x += (float) delta;
}

void MapTile::changeLocationY(int delta)
{
	this->y += (float) delta;
}

int MapTile::getLocationX()
{
	return (int) x;
}

int MapTile::getLocationY()
{
	return (int) y;
}

int MapTile::getHeight()
{
	return (int) toDraw[0].getSize().y;
}

int MapTile::getWidth()
{
	return (int) toDraw[0].getSize().x;
}
