#include "Animals.h"

Animal::Animal()
{
	_x = GAME_LEFT_BOUND + 1;
	_y = GAME_BOTTOM_BOUND;
}

Animal::Animal(int x, int y)
{
	_x = x;
	_y = y;
}

void Animal::move(Buffer buffer)
{
	_x++;
	if (_x >= GAME_RIGHT_BOUND - 2)
	{
		buffer[_y][_x + 1].character = ' ';
		buffer[_y][_x].character = ' ';
		buffer[_y][_x - 1].character = ' ';
		buffer[_y + 1][_x + 1].character = ' ';
		buffer[_y + 1][_x].character = ' ';
		buffer[_y + 1][_x - 1].character = ' ';
		_x = GAME_LEFT_BOUND + 1;
	}

}