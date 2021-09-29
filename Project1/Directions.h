#pragma once

enum Direction { UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4 };
Direction getDirectionFromInt(int i);
Direction reverseDirection(Direction d);
Direction turnClockwise(Direction d, int numberOfQuarters);