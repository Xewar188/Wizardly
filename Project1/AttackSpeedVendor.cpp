#include "AttackSpeedVendor.h"
#include "Player.h"

AttackSpeedVendor::AttackSpeedVendor()
{
}

AttackSpeedVendor::AttackSpeedVendor(float width, float height, float x, float y, Board* board)
	:Vendor(width, height, x, y, board)
{
	cost = 100;
	toDraw[0].setFillColor(Color(179, 94, 230));
}

void AttackSpeedVendor::buy(Player* target)
{
	target->increaseAttackSpeed(2);
}
