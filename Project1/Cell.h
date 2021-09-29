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

	bool isTangible = false;//czy kafelek wywoluje kolizje
	bool filled = false;//zmienna u¿ywana podczas tworzenia planszy by okreslic czy cos zostalo w nim umieszczone

	sf::RectangleShape rect;//glowne tlo kafelka
	std::vector<sf::RectangleShape> toDraw;//dodatkowe elementy estetyczne
public:
	Cell();

	float getX();//zwraca x

	float getY();//zwraca y

	void draw(sf::RenderTarget& window, sf::RenderStates state) const;

	void setFilled(bool isFilled);

	bool isFilled();

	bool isCellTangible();

	virtual void hit(int dmg) {}
	virtual void update() {}
	virtual void onInteract(Player* cel);
};