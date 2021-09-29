#include "HealthVendor.h"
#include "Player.h"
HealthVendor::HealthVendor()
{
}

HealthVendor::HealthVendor(float width, float height, float x, float y, Board* board)
	:Vendor(width, height, x, y, board)
{
	toDraw[0].setFillColor(Color(140, 215, 216));
	cost = 100;
}

void HealthVendor::buy(Player* target)
{
	target->increaseHealth(35);
	target->heal(35);
}
