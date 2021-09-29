#include "Healpoint.h"
#include "Player.h"
#include "Board.h"

#include "Directions.h"
#include "MapTile.h"
Healpoint::Healpoint()
{

}
Healpoint::Healpoint(float width, float height, float xa, float ya, Board* boarda)
{

	board = boarda;
	weight = 5;
	strength = 0;
	mode = NEUTRAL;
	body = RectangleShape(Vector2f(width, height));
	x = (int)std::floor((xa + body.getSize().x / 2) / board->getCellWidth());
	y = (int)std::floor((ya + body.getSize().y / 2) / board->getCellHeight());
	direction = getDirectionFromInt(0);
	movable = true;
	isTangible = true;
	interactable = true;
	body.setFillColor(Color(89, 89, 89));
	body.setPosition(xa, ya);
	uses = rand() % 3 + 1;
	switch (uses)
	{
	case 3:
		toDraw.push_back(RectangleShape(Vector2f(width / 12, height / 12)));
		toDraw[toDraw.size() - 1].setFillColor(Color::Red);
		toDraw.push_back(RectangleShape(Vector2f(width / 12, height / 12)));
		toDraw[toDraw.size() - 1].setFillColor(Color::Red);
		toDraw.push_back(RectangleShape(Vector2f(width / 12, height / 12)));
		toDraw[toDraw.size() - 1].setFillColor(Color::Red);

	case 2:
		toDraw.push_back(RectangleShape(Vector2f(width / 2, height / 12)));
		toDraw[toDraw.size() - 1].setFillColor(Color::Red);
		toDraw[toDraw.size() - 1].setRotation(-30);
		toDraw.push_back(RectangleShape(Vector2f(width / 18 * 5, height / 18 * 5)));
		toDraw[toDraw.size() - 1].setFillColor(Color(205, 0, 0));
	case 1:
		toDraw.push_back(RectangleShape(Vector2f(width / 6, height / 6)));
		toDraw[toDraw.size() - 1].setFillColor(Color::Red);
		toDraw.push_back(RectangleShape(Vector2f(width / 3, height / 3)));
		toDraw[toDraw.size() - 1].setFillColor(Color(205, 0, 0));

	}
	
	std::reverse(toDraw.begin(), toDraw.end());
	setAppearance();
	board->getMap()->addHealing(uses);
	board->getMap()->update();
}
void Healpoint::onInteract(Player* cel)
{
	if (uses > 0 && cel->getHealth() != cel->getMaxHealth())
	{
		cel->heal((int)cel->getMaxHealth() / 5);
		uses--;
		int piecesToColor = 0;
		if (uses == 2)
			piecesToColor = 3;
		else
			piecesToColor = 2;
		for (int i = 0; i < piecesToColor; i++)
		{
			toDraw[uses * 2 + i].setFillColor(Color(0, 204, 255));
		}
		board->getMap()->useHealing();
		board->getMap()->update();
	}
}
void Healpoint::setAppearance()
{
	switch (toDraw.size())
	{
	case 7:


		toDraw[6].setPosition(body.getPosition().x + body.getSize().x / 6,
								body.getPosition().y + body.getSize().y / 6);

		toDraw[5].setPosition(body.getPosition().x + body.getSize().x / 3,
								body.getPosition().y + body.getSize().y / 6);

		toDraw[4].setPosition(body.getPosition().x + body.getSize().x / 2,
								body.getPosition().y + body.getSize().y / 6);

	case 4:
		toDraw[3].setPosition(body.getPosition().x + body.getSize().x / 3, 
								body.getPosition().y + body.getSize().y / 3 * 2);
		toDraw[2].setPosition(body.getPosition().x + body.getSize().x / 10 * 6,
								body.getPosition().y + body.getSize().y / 3);

	case 2:
		toDraw[1].setPosition(body.getPosition().x + body.getSize().x / 4, 
								body.getPosition().y + body.getSize().y * 7 / 12);

		toDraw[0].setPosition(body.getPosition().x + body.getSize().x / 6, 
								body.getPosition().y + body.getSize().y / 2);
	}
}