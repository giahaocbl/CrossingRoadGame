#include "Game.h"
#include <thread>


Game *g;
char Cmove;
Buffer buffer;
bool isRUNNING = true;



void SubThread()
{
	GotoXY(0, 0);
	g->drawLogo();
	g->drawGameBoard(buffer);
	while (isRUNNING)
	{
		if (!g->getPeople().isDead())
		{
			g->updatePosPeople(Cmove, buffer);
		}

		Cmove = ' ';
		if (g->getTrafficLight().getLight() == green)
			g->updatePosVehicle(buffer);
		g->updatePosAnimal(buffer);
		g->showMenuIngame();
		if (Game::MUTE == 0)
			g->animalTell();
		g->traffic();
		g->drawGame(buffer);
		int lv = g->getLevel();

		if (g->getPeople().isImpact(g->getBird(), lv) || g->getPeople().isImpact(g->getDinosaur(), lv) || g->getPeople().isImpact(g->getCar(), lv) || g->getPeople().isImpact(g->getTruck(), lv))
		{
			if (Game::MUTE == 0)
				mciSendStringA("play audio/die.mp3", 0, NULL, 0);
			g->dieEffect(buffer);
			isRUNNING = false;
		}
	
		if (g->getPeople().isFinish())
		{
			mciSendStringA("play audio/level.mp3", 0, NULL, 0);
			TextColor(7);
			GotoXY(GAME_RIGHT_BOUND + 5, GAME_TOP_BOUND + 2);
			cout << "Level: " << (g->getLevel() + (g->getLevel() < 4));
			g->levelUp();
			g->resetGame(g->getLevel(), buffer);
			g->drawGameBoard(buffer);
		}
	}
	
}

void StartGame()
{
	GotoXY(GAME_LEFT_BOUND + 20, 1);
	cout << "                                            ";
	char temp;
	thread t1(SubThread);
	while (1)
	{
		temp = toupper(_getch());
		if (isRUNNING)
		{
			if (temp == 27)
			{
				g->exitGame(t1.native_handle());
				return;
			}
			else if (temp == 'P')
				g->pauseGame(t1.native_handle());
			else if (temp == 'L')
			{
				g->pauseGame(t1.native_handle());
				g->saveGame();
			}
			else if (temp == 'T')
			{
				g->pauseGame(t1.native_handle());
				g->loadGame();
				g->drawGameBoard(buffer);
				g->showMenuIngame();
				g->drawGame(buffer);
				g->pauseGame(t1.native_handle());
			}
			else
			{
				g->resumeGame(t1.native_handle());
				Cmove = temp;
			}
		}
		else
		{
			if (temp == 'Y')
			{
				system("cls");
				if (Game::MUTE == 0)
					mciSendStringA("stop audio/ambulance.mp3", 0, NULL, 0);
				isRUNNING = 1;
				g->resetGame(MIN_LV, buffer);
				StartGame();
			}
			else
			{
				g->exitGame(t1.native_handle());
				return;
			}
		}
	}
}

void main()
{
	g = new Game();
	FixConsoleWindow();
	Nocursortype();
	g->login(buffer);
	GotoXY(0, 0);
	system("cls");
	for (int i = 0; i < 100; i++)
	{
		GotoXY(55, 10);
		cout << "LOADING: " << i + 1 << "%";
		if (i % 5 == 0)
		{
			TextColor(10);
			GotoXY(55 + i / 5, 13);
			cout << char(219);
			GotoXY(55 + i / 5, 14);
			cout << char(219);
			TextColor(7);
		}

		Sleep(10);
	}
	Sleep(500);
	system("cls");
	StartGame();
}