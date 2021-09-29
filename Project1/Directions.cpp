#include "Directions.h"
Direction getDirectionFromInt(int i) {
	switch (i)
	{
	case 1:
		return UP;
	case 2:
		return RIGHT;
	case 3:
		return DOWN;
	case 4:
		return LEFT;
	default:
		return UP;
		break;
	}
}
Direction reverseDirection(Direction d) {
	return getDirectionFromInt((d + 1) % 4 + 1);
}
Direction turnClockwise(Direction d, int numberOfQuarters) {
	return getDirectionFromInt((d + numberOfQuarters - 1) % 4 + 1);
}