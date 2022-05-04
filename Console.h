#pragma once
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <Windows.h>
#include <iostream>
#pragma comment(lib,"winmm.lib")


using namespace std;

#define consoleWidth 120
#define consoleHeight 29

#define GAME_LEFT_BOUND 10
#define GAME_RIGHT_BOUND 90
#define GAME_TOP_BOUND 5
#define GAME_BOTTOM_BOUND 25

#define birdColor 10
#define dinosaurColor 4
#define carColor 14
#define truckColor 11;
#define manColor 12

#define Y_CAR 9
#define Y_BIRD 13
#define Y_TRUCK 17
#define Y_DINOSAUR 21

struct Cell
{
	int color;
	char character;
};


typedef Cell Buffer[consoleHeight][consoleWidth];



void FixConsoleWindow();
void GotoXY(int x, int y);
void Nocursortype();
void TextColor(int color);


#endif // !CONSOLE_H_
