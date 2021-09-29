#include "Artifact.h"
#include "Player.h"
#include "Board.h"
#include "MapTile.h"
#include "Directions.h"

Artifact::Artifact(float width, float height, float xa, float ya, Color color, Board* boarda, int mod)
{
	board = boarda;
	weight = 0;
	strength = 0;
	mode = FRIEND;
	vel = 0;

	body = RectangleShape(Vector2f(width / 2, height / 2));
	body.setPosition(Vector2f(xa, ya));
	body.setFillColor(color);
	setMapCoordinates();

	this->mod = mod;
	direction = UP;

	maxHealth = 200000;
	health = maxHealth;


	isTangible = false;
	interactable = true;
	movable = false;
}
void Artifact::onInteract(Player* cel)
{
	body.setPosition(board->getCell(1, 0)->getX() / 2, 
						board->getCell(0, 1)->getY() / 2);
	body.rotate((float)(90 * mod));
	cel->addPiece(body);

	cel->increaseArtifactCounter();
	remove();
	cel->givePoints(200);
	cel->board->getMap()->useShrine();
	cel->board->getMap()->update();
	cel->unlockWeapon();
}