#include "Settings.h"
#include "MapTile.h"
class Map
{
	int xmiddle = 0, ymiddle = 0;
public:
	MapTile maps[BOARD_NUMBER][BOARD_NUMBER];
	void show(sf::RenderWindow& window);
	void setAppearance();
	void move(int dir);
};

