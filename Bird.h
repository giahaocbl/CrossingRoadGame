#pragma once
#ifndef _BIRD_H_
#define _BIRD_H_

#include "Animals.h"


class Bird :public Animal
{
public:
	Bird() :Animal() { _y = Y_BIRD; };
	Bird(int x, int y) :Animal(x, y) {};
	void draw(Buffer buffer)
	{
		if (_x - 1 > GAME_LEFT_BOUND)
		{
			buffer[_y][_x - 1].character = ' ';
			buffer[_y][_x - 1].color = 7;
		}

		buffer[_y][_x].character = ' ';
		buffer[_y][_x].color = 7;

		buffer[_y][_x + 1].character = ' ';
		buffer[_y][_x + 1].color = 7;

		buffer[_y][_x].character = 223;
		buffer[_y][_x].color = birdColor;

		buffer[_y][_x + 1].character = 220;
		buffer[_y][_x + 1].color = birdColor;

		buffer[_y][_x + 2].character = 223;
		buffer[_y][_x + 2].color = birdColor;

	};
	void tell()
	{
		mciSendStringA("play audio/bird.mp3", 0, NULL, 0);
	}
};


#endif // !BIRD_H_
