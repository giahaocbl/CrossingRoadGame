#pragma once
#ifndef _TRUCK_H_
#define _TRUCK_H_

#include "Vehicle.h"



class Truck :public Vehicle
{
public:
	Truck() :Vehicle() { _y = Y_TRUCK; };
	Truck(int x, int y) :Vehicle(x, y) {};
	void draw(Buffer buffer)
	{
		buffer[_y][_x + 3].character = ' ';
		buffer[_y][_x + 3].color = 7;

		buffer[_y][_x].character = 220;
		buffer[_y][_x].color = truckColor;

		buffer[_y][_x + 1].character = 219;
		buffer[_y][_x + 1].color = truckColor;

		buffer[_y][_x + 2].character = 219;
		buffer[_y][_x + 2].color = truckColor;
	}
};


#endif // !Truck_H_
