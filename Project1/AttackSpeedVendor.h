#pragma once
#include "Vendor.h"
class AttackSpeedVendor : public Vendor
{
	
public:
	AttackSpeedVendor();// mode -0
	AttackSpeedVendor(float width, float height, float x, float y, Board* board);
	virtual void buy(Player* target);
};