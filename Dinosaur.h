#pragma once
#ifndef _DINOSAUR_H_
#define _DINOSAUR_H_

#include "Animals.h"


class Dinosaur :public Animal
{
public:
	Dinosaur() :Animal() { _y = Y_DINOSAUR; };
	Dinosaur(int x, int y) :Animal(x, y) {};
	void draw(Buffer buffer)
	{
		if (_x - 1 > GAME_LEFT_BOUND)
		{
			buffer[_y + 1][_x - 1].character = ' ';
			buffer[_y + 1][_x - 1].color = 7;
		}

		buffer[_y][_x + 1].character = ' ';
		buffer[_y][_x + 1].color = 7;

		buffer[_y + 1][_x].character = ' ';
		buffer[_y + 1][_x].color = 7;

		buffer[_y + 1][_x + 1].character = ' ';
		buffer[_y + 1][_x + 1].color = 7;

		buffer[_y][_x + 2].character = 220;
		buffer[_y][_x + 2].color = dinosaurColor;

		buffer[_y + 1][_x].character = 220;
		buffer[_y + 1][_x].color = dinosaurColor;

		buffer[_y + 1][_x + 1].character = 219;
		buffer[_y + 1][_x + 1].color = dinosaurColor;

		buffer[_y + 1][_x + 2].character = 223;
		buffer[_y + 1][_x + 2].color = dinosaurColor;

	}

	void tell()
	{
		mciSendStringA("play audio/dinosaur.mp3", 0, NULL, 0);
	}
};


#endif // !Dinosaur_H_


