#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Board;
class MapTile : public sf::Drawable
{

	std::vector<sf::RectangleShape> toDraw;
	std::vector<sf::RectangleShape> chestsShape;
	std::vector<sf::RectangleShape> chestsTopShape;
	std::vector<sf::RectangleShape> healShape;
	std::vector<sf::RectangleShape> vendorShape;
	sf::RectangleShape shrineShape;
	bool isShrine = false;
	int shrineType = 0;
	sf::RectangleShape veil = sf::RectangleShape();
	int healing = 0;
	int chests = 0;
	int vendors = 0;
	float x = 100, y = 100;
	bool found = false;
	Board* boarda = NULL;

	public:
	MapTile() {}
	MapTile(Board& board, sf::Vector2u window);
	void setAppearance();
	void update();
	virtual void draw(sf::RenderTarget& window, sf::RenderStates state) const;
	
	void useShrine();
	void setShrine(int type);
	bool hasShrine();
	void find();
	void addHealing(int i);
	void useHealing();
	int healingLeft();
	void addChest();
	void useChest();
	void addVendor();
	void useVendor();
	
	void setMainStatus();
	void removeMainStatus();
	void setLocationX(int x);
	void setLocationY(int y);
	void changeLocationX(int delta);
	void changeLocationY(int delta);
	int getLocationX();
	int getLocationY();
	int getHeight();
	int getWidth();
};