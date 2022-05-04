#include "People.h"



People::People()
{
	_x = (GAME_LEFT_BOUND + GAME_RIGHT_BOUND) / 2;;
	_y = GAME_BOTTOM_BOUND - 2;
	_isAlive = true;
}

People::People(int x, int y)
{
	_x = x;
	_y = y;
	_isAlive = true;
}

void People::reset()
{
	_x = (GAME_LEFT_BOUND + GAME_RIGHT_BOUND) / 2;
	_y = GAME_BOTTOM_BOUND - 2;
	_isAlive = true;
}

void People::moveUp(Buffer buffer)
{
	buffer[_y][_x].character = ' ';
	buffer[_y][_x].color = 7;
	if (_y > GAME_TOP_BOUND + 1)
		_y--;

}

void People::moveDown(Buffer buffer)
{
	buffer[_y][_x].character = ' ';
	buffer[_y][_x].color = 7;
	if (_y < GAME_BOTTOM_BOUND - 1)
		_y++;
}

void People::moveLeft(Buffer buffer)
{
	buffer[_y][_x].character = ' ';
	buffer[_y][_x].color = 7;
	if (_x > GAME_LEFT_BOUND + 1)
		_x--;
}

void People::moveRight(Buffer buffer)
{
	buffer[_y][_x].character = ' ';
	buffer[_y][_x].color = 7;
	if (_x < GAME_RIGHT_BOUND - 1)
		_x++;
}

bool People::isFinish()
{
	return _y == GAME_TOP_BOUND + 1;
}

bool People::isDead()
{
	return !_isAlive;
}

void People::draw(Buffer buffer)
{
	buffer[_y][_x].character = 'Y';
	buffer[_y][_x].color = manColor;
}

bool People::isImpact(Bird* b, int lv) 
{
	for (int i = 0; i < lv + 2; i++)
	{
		if ((_x >= b[i].X()) && (_x <= b[i].X() + 2) && (_y == b[i].Y()))
		{
			_isAlive = false;
			return true;
		}
	}
	return false;
}

bool People::isImpact(Dinosaur* d, int lv)
{
	for (int i = 0; i < lv + 2; i++)
	{
		if (((_y == d[i].Y() + 1) && (_x >= d[i].X()) && (_x <= d[i].X() + 2)) || ((_x == d[i].X() + 2) && (_y == d[i].Y())))
		{
			_isAlive = false;
			return true;
		}
	}
	return false;
}


bool People::isImpact(Car* c, int lv)
{
	for (int i = 0; i < lv + 2; i++)
	{
		if ((_x >= c[i].X()) && (_x <= c[i].X() + 3) && (_y == c[i].Y()))
		{
			_isAlive = false;
			return true;
		}
	}
	return false;
}

bool People::isImpact(Truck* t, int lv)
{
	for (int i = 0; i < lv + 2; i++)
	{
		if ((_x >= t[i].X()) && (_x <= t[i].X() + 2) && (_y == t[i].Y()))
		{
			_isAlive = false;
			return true;
		}
	}
	return false;
}

