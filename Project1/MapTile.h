#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Board;
class MapTile : public sf::Drawable
{

	std::vector<sf::RectangleShape> toDraw;//podstawowy wyglad mapy
	std::vector<sf::RectangleShape> chestsShape;//skrzynie
	std::vector<sf::RectangleShape> chestsTopShape;
	std::vector<sf::RectangleShape> healShape;//ilosc leczenia
	std::vector<sf::RectangleShape> vendorShape;
	sf::RectangleShape shrineShape;//shrine
	bool isShrine = false;//czy dana mapa posiada shrine
	int shrineType = 0;//typ shrine
	sf::RectangleShape veil = sf::RectangleShape();//zaslona(pokazywana gdy dana mapa nie jest odkryta)
	int healing = 0;//ilosc leczen
	int chests = 0;//ilosc skrzyn
	int vendors = 0;
	float x = 100, y = 100;//polozenie x,y lewego gornego rogu mapy 
	bool found = false;//czy zostala odkryta
	Board* boarda = NULL;//plansza za ktora odpowiada dana mapa

	public:
	MapTile() {}
	MapTile(Board& board, sf::Vector2u window);
	void setAppearance();//dostosowywuje wyglad do polozenia
	void update();//aktualizuje zawartosc mapy (ilosc leczen, skrzyn etc)
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