#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Player;
class Board;
class Cell : public sf::Drawable
{
protected:
	int x, y;

	Board *src;

	bool isTangible = false;
	bool filled = false;

	sf::RectangleShape rect;
	std::vector<sf::RectangleShape> toDraw;
public:
	Cell();

	float getX();

	float getY();

	void draw(sf::RenderTarget& window, sf::RenderStates state) const;

	void setFilled(bool isFilled);

	bool isFilled();

	bool isCellTangible();

	virtual void hit(int dmg) {}
	virtual void update() {}
	virtual void onInteract(Player* cel);
};