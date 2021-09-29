#pragma once
#include <SFML\Graphics.hpp>

enum Direction;
class Board;
class Entity;
class Projectile : public sf::Drawable
{
	bool isInWall();
protected:
	sf::RectangleShape body;//glowne cialo pocisku
	std::vector<sf::RectangleShape> toDraw;//dodatkowe czesci wygladu
	int damage;//obrazenia pocisku
	int vela;//predkosc pocisku
	Direction dir;//kierunek pocisku
	int x, y;//wspolzedne x,y obecnego kafelka
	int type = 0; //<0 dla przyjaznych 0> dla wrogich 
	int projectileId;
	Board* board;//mapa na ktorej znajduje sie pocisk
public:
	Projectile();
	Projectile(Entity c, Board& board);

	bool equals(Projectile* toCompare);
	int getDamage();
	int getType();
	sf::FloatRect getGlobalBounds();

	virtual int getCenterX();
	virtual int getCenterY();
	virtual void draw(sf::RenderTarget& window, sf::RenderStates state) const;
	bool isOnMap();
	virtual bool move(int vel = -1);//poruszanie pociskiem zwraca true jezeli przerwany przedwczesnie
	
	virtual void remove();//usuwanie pocisku z mapy
	virtual bool hitEntity( Entity* toHit) { return true; }; //zachowanie podczas trafienia objektu   zwraca true jezeli pocisk jest usuwany false jezeli nie
	virtual void hitWall() {};//zachowanie podczas trafienia sciany
	virtual void setAppearance(){}//dostosowanie wygladu do nowegoc polozenia
	virtual void animate() {}//zmiana wygladu ze wzgledu na animacje
};







