#pragma once
#ifndef _CAR_H_
#define _CAR_H_

#include "Vehicle.h"


class Car :public Vehicle
{
public:
	Car() :Vehicle() { _y = Y_CAR; };
	Car(int x, int y) :Vehicle(x, y) {};
	void draw(Buffer buffer)
	{
		buffer[_y][_x + 4].character = ' ';
		buffer[_y][_x + 4].color = 7;

		buffer[_y][_x].character = 220;
		buffer[_y][_x].color = carColor;

		buffer[_y][_x + 1].character = 219;
		buffer[_y][_x + 1].color = carColor;

		buffer[_y][_x + 2].character = 219;
		buffer[_y][_x + 2].color = carColor;

		buffer[_y][_x + 3].character = 220;
		buffer[_y][_x + 3].color = carColor;
	}
};


#endif // !Car_H_
