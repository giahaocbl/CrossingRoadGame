#pragma once
#ifndef _PEOPLE_H_
#define _PEOPLE_H_

#include "Bird.h"
#include "Dinosaur.h"
#include "Car.h"
#include "Truck.h"


class People
{
private:
	int _x, _y;
	bool _isAlive;
public:
	People();
	People(int, int);
	int X() { return _x; }
	int Y() { return _y; }
	void set(int x, int y) { _x = x; _y = y; }
	void reset();
	void moveUp(Buffer buffer);
	void moveDown(Buffer buffer);
	void moveLeft(Buffer buffer);
	void moveRight(Buffer buffer);
	void draw(Buffer buffer);
	bool isFinish();
	bool isDead();
	bool isImpact(Bird*, int);
	bool isImpact(Dinosaur*, int);
	bool isImpact(Car*, int);
	bool isImpact(Truck*, int);
	void setAliveFalse() { _isAlive = false; }
};

#endif // !PEOPLE_H_
