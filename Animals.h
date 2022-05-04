#pragma once
#ifndef _ANIMALS_H_
#define _ANIMALS_H_

#include "Console.h"
#include <ctime>

class Animal
{
protected:
	int _x, _y;
public:
	Animal();
	Animal(int, int);
	virtual void move(Buffer buffer);
	virtual void tell() {};
	virtual void draw(Buffer) = 0;
	int X() { return _x; }
	int Y() { return _y; }
	void set(int x, int y) {
		_x = x;
		_y = y;
	}
};





#endif // !ANIMALS_H_
