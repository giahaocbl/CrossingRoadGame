#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include "People.h"
#include "TrafficLight.h"
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <string>


#define _CRT_SECURE_NO_WARNINGS


#define MIN_LV 1
#define MAX_LV 4

class Game
{
private:
	People _people;
	Bird* _bird;
	Car* _car;
	Truck* _truck;
	Dinosaur* _dinosaur;
	TrafficLight _light;
	int _level;
public:
	static bool MUTE;
	Game();
	~Game();
	void drawGame(Buffer buffer);
	void Init(int);
	void updatePosPeople(char, Buffer);
	void updatePosAnimal(Buffer);
	void animalTell();
	void updatePosVehicle(Buffer);
	void traffic();
	void levelUp();
	Truck* getTruck();
	Bird* getBird();
	Dinosaur* getDinosaur();
	Car* getCar();
	People getPeople();
	TrafficLight getTrafficLight();
	int getLevel();
	void resetGame(int, Buffer);
	void drawGameBoard(Buffer);
	void dieEffect(Buffer);
	void exitGame(HANDLE);
	void showMenuIngame();
	bool loadGame();
	void saveGame();
	void pauseGame(HANDLE);
	void resumeGame(HANDLE);
	void login(Buffer);
	void gameSetting(Buffer);
	int pickLevel();
	void drawBorder(int);
	void drawLogo();
};


#endif // !GAME_H_
