#include "Settings.h"
#include "MapTile.h"
class Map
{
	int xmiddle = 0, ymiddle = 0;//wspolrzedne x i y w tablicy map srodkowej mapy ukladu
public:
	MapTile maps[BOARD_NUMBER][BOARD_NUMBER];//wszystkie mapy
	void show(sf::RenderWindow& window);//wyswietlenie map
	void setAppearance();//dostosowanie wygladu map po przesunieciu
	void move(int dir);//przesuniecie ukladu map
};

