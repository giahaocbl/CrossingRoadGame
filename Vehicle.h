#pragma once
#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include "Console.h"


class Vehicle
{
protected:
	int _x, _y;
public:
	Vehicle();
	Vehicle(int, int);
	virtual void move(Buffer);
	virtual void draw(Buffer) = 0;
	int X() { return _x; }
	int Y() { return _y; }
	void set(int x, int y) {
		_x = x;
		_y = y;
	}
};


#endif // !ANIMALS_H_
