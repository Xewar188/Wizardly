#pragma once
#include <SFML\Graphics.hpp>

enum Direction;
class Board;
class Entity;
class Projectile : public sf::Drawable
{
	bool isInWall();
protected:
	sf::RectangleShape body;
	std::vector<sf::RectangleShape> toDraw;
	int damage;
	int vela;
	Direction dir;
	int x, y;
	int type = 0; 
	int projectileId;
	Board* board;
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
	virtual bool move(int vel = -1);
	
	virtual void remove();
	virtual bool hitEntity( Entity* toHit) { return true; }; 
	virtual void hitWall() {};
	virtual void setAppearance(){}
	virtual void animate() {}
};







