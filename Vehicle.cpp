#include "Vehicle.h"

Vehicle::Vehicle()
{
	_x = GAME_RIGHT_BOUND - 5;
	_y = GAME_BOTTOM_BOUND;
}

Vehicle::Vehicle(int x, int y)
{
	_x = x;
	_y = y;
}

void Vehicle::move(Buffer buffer)
{
	_x--;
	if (_x <= GAME_LEFT_BOUND)
	{
		buffer[_y][_x + 1].character = ' ';
		buffer[_y][_x + 4].character = ' ';
		buffer[_y][_x + 2].character = ' ';
		buffer[_y][_x + 3].character = ' ';

		_x = GAME_RIGHT_BOUND - 5;
	}
}
