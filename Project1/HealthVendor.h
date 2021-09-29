#pragma once
#pragma once
#include "Vendor.h"
class HealthVendor : public Vendor
{
public:
	HealthVendor();
	HealthVendor(float width, float height, float x, float y, Board* board);
	virtual void buy(Player* target);
};