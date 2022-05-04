#include "Game.h"

bool Game::MUTE = 0;

Game::Game()
{
	_level = MIN_LV;
	Init(_level);
}

Game::~Game()
{
	delete[] _bird;
	delete[] _dinosaur;
	delete[] _car;
	delete[] _truck;
}

void Game::Init(int level)
{
	_level = level;
	_bird = new Bird[_level + 2];
	_dinosaur = new Dinosaur[_level + 2];
	_car = new Car[_level + 2];
	_truck = new Truck[_level + 2];
	for (int i = 0; i < _level + 2; i++)
	{
		int x_animals = GAME_LEFT_BOUND + 1 + i * (80 / (_level + 3));
		int x_vehicle = GAME_RIGHT_BOUND - 5 - i * (80 / (_level + 3));
		_bird[i].set(x_animals, Y_BIRD);
		_dinosaur[i].set(x_animals, Y_DINOSAUR);
		_car[i].set(x_vehicle, Y_CAR);
		_truck[i].set(x_vehicle, Y_TRUCK);
	}
}

void Game::levelUp()
{
	TextColor(4);
	_level++;
	delete[] _bird;
	delete[] _dinosaur;
	delete[] _car;
	delete[] _truck;
	if (_level == 5)
	{
		char h = 223, l = 220, f = 219;
		GotoXY(GAME_RIGHT_BOUND + 3, GAME_TOP_BOUND + 10);
		cout << h << l << " " << l << h << " " << l << h << h << l << " " << f << "  " << f;
		GotoXY(GAME_RIGHT_BOUND + 5, GAME_TOP_BOUND + 11);
		cout << f << "   " << h << l << l << h << " " << h << l << l << h;
		GotoXY(GAME_RIGHT_BOUND + 3, GAME_TOP_BOUND + 13);
		cout << f << "  " << l << "  " << f << " " << f << " " << f << h << l << "  " << f;
		GotoXY(GAME_RIGHT_BOUND + 4, GAME_TOP_BOUND + 14);
		cout << h << l << h << l << h << "  " << f << " " << f << "  " << h << l << f;
		_getch();
		exit(0);
	}
	_people.reset();
	Init(_level);
}



void Game::drawGame(Buffer buffer)
{
	_people.draw(buffer);
	for (int i = 0; i < _level + 2; i++)
	{
		_bird[i].draw(buffer);
		_dinosaur[i].draw(buffer);
		_car[i].draw(buffer);
		_truck[i].draw(buffer);
	}



	if (_light.getLight() == red)
	{
		buffer[Y_CAR][GAME_LEFT_BOUND].character = 223;
		buffer[Y_TRUCK][GAME_LEFT_BOUND].character = 223;
		buffer[Y_CAR][GAME_LEFT_BOUND].color = 4;
		buffer[Y_TRUCK][GAME_LEFT_BOUND].color = 4;
	}
	else
	{
		buffer[Y_CAR][GAME_LEFT_BOUND].character = 220;
		buffer[Y_TRUCK][GAME_LEFT_BOUND].character = 220;
		buffer[Y_CAR][GAME_LEFT_BOUND].color = 10;
		buffer[Y_TRUCK][GAME_LEFT_BOUND].color = 10;
	}

	for (int i = GAME_TOP_BOUND; i <= GAME_BOTTOM_BOUND; i++)
	{
		GotoXY(GAME_LEFT_BOUND, i);

		for (int j = GAME_LEFT_BOUND; j <= GAME_RIGHT_BOUND; j++)
		{
			TextColor(buffer[i][j].color);
			putchar(buffer[i][j].character);
		}
	}
	TextColor(7);
}

void Game::updatePosPeople(char c, Buffer buffer)
{
	switch (c)
	{
	case 'a':
	case 'A': _people.moveLeft(buffer); break;
	case 'w':
	case 'W': _people.moveUp(buffer); break;
	case 's':
	case 'S': _people.moveDown(buffer); break;
	case 'd':
	case 'D': _people.moveRight(buffer); break;
	}
}

void Game::updatePosAnimal(Buffer buffer)
{
	for (int i = 0; i < _level + 2; i++)
	{
		_bird[i].move(buffer);
		_bird[i].draw(buffer);
		_dinosaur[i].move(buffer);
		_dinosaur[i].draw(buffer);
	}
}

void Game::animalTell()
{
	_bird[0].tell();
	_dinosaur[0].tell();
}

void Game::updatePosVehicle(Buffer buffer)
{
	for (int i = 0; i < _level + 2; i++)
	{
		_car[i].move(buffer);
		_car[i].draw(buffer);
		_truck[i].move(buffer);
		_truck[i].draw(buffer);
	}
}

void Game::traffic()
{
	_light.updateTime();
}

Bird* Game::getBird()
{
	return _bird;
}

Dinosaur* Game::getDinosaur()
{
	return _dinosaur;
}

Car* Game::getCar()
{
	return _car;
}

Truck* Game::getTruck()
{
	return _truck;
}

TrafficLight Game::getTrafficLight()
{
	return _light;
}

People Game::getPeople()
{
	return _people;
}

int Game::getLevel()
{
	return _level;
}


void Game::resetGame(int level, Buffer buffer)
{
	for (int i = GAME_TOP_BOUND + 1; i < GAME_BOTTOM_BOUND; i++)
		for (int j = GAME_LEFT_BOUND + 1; j < GAME_RIGHT_BOUND; j++)
		{
			buffer[i][j].character = ' ';
			buffer[i][j].color = 7;
		}
	_level = level;
	_people.reset();
	Init(_level);
}

void Game::drawGameBoard(Buffer buffer)
{
	for (int i = GAME_TOP_BOUND; i <= GAME_BOTTOM_BOUND; i++)
		for (int j = GAME_LEFT_BOUND; j <= GAME_RIGHT_BOUND; j++)
		{
			if (i == GAME_TOP_BOUND)
			{
				buffer[i][j].character = 220;
				buffer[i][j].color = 6;
			}
			else if (i == GAME_BOTTOM_BOUND)
			{
				buffer[i][j].character = 223;
				buffer[i][j].color = 6;
			}
			else
			{
				if (j == GAME_LEFT_BOUND || j == GAME_RIGHT_BOUND)
				{
					buffer[i][j].character = 219;
					buffer[i][j].color = 6;
				}
				else
				{
					buffer[i][j].character = ' ';
					buffer[i][j].color = 7;
				}
			}
		}
}

void Game::dieEffect(Buffer buffer)
{
	int x = _people.X();
	int y = _people.Y();
	for (int i = 0; i < 4; i++)
	{
		GotoXY(x, y);
		cout << ' ';
		Sleep(300);
		GotoXY(x, y);
		TextColor(manColor);
		cout << "Y";
		Sleep(300);
		TextColor(7);
	}
	TextColor(4);

	char h = 223, l = 220, f = 219, s = ' ';
	GotoXY(GAME_RIGHT_BOUND + 3, GAME_TOP_BOUND + 10);
	cout << h << l << " " << l << h << " " << l << h << h << l << " " << f << "  " << f;
	GotoXY(GAME_RIGHT_BOUND + 5, GAME_TOP_BOUND + 11);
	cout << f << "   " << h << l << l << h << " " << h << l << l << h;
	GotoXY(GAME_RIGHT_BOUND + 3, GAME_TOP_BOUND + 13);
	cout << f << s << s << s << l << h << h << l << s << s << l << h << h << l << s << f << h << h;
	GotoXY(GAME_RIGHT_BOUND + 3, GAME_TOP_BOUND + 14);
	cout << f << s << s << s << f << s << s << f << s << l << s << h << l << s << s << f << h << h;
	GotoXY(GAME_RIGHT_BOUND + 3, GAME_TOP_BOUND + 15);
	cout << h << h << h << s << s << h << h << s << s << s << h << h << s << s << s << h << h << h;

	if (Game::MUTE == 0)
		mciSendStringA("play audio/ambulance.mp3", 0, NULL, 0);
	GotoXY((GAME_LEFT_BOUND + GAME_RIGHT_BOUND) / 2 - 15, 3);
	cout << "Press Y to restart!";
	TextColor(7);
}


void Game::showMenuIngame()
{
	TextColor(14);
	GotoXY((GAME_LEFT_BOUND + GAME_RIGHT_BOUND) / 2 - 15, 3);
	cout << "                                          ";
	GotoXY((GAME_LEFT_BOUND + GAME_RIGHT_BOUND) / 2 - 15, 4);
	cout << "                                          ";
	GotoXY(GAME_RIGHT_BOUND + 5, GAME_TOP_BOUND + 2);
	cout << "Level: " << _level;
	GotoXY(GAME_RIGHT_BOUND + 5, GAME_TOP_BOUND + 4);
	cout << "Press T to load game";
	GotoXY(GAME_RIGHT_BOUND + 5, GAME_TOP_BOUND + 5);
	cout << "Press L to save game";
	GotoXY(GAME_RIGHT_BOUND + 5, GAME_TOP_BOUND + 6);
	cout << "Press P to pause game";
	GotoXY(GAME_RIGHT_BOUND + 5, GAME_TOP_BOUND + 7);
	cout << "Press ESC to exit";
	TextColor(7);
}

void Game::exitGame(HANDLE _t)
{
	exit(0);
}

void Game::pauseGame(HANDLE _t)
{
	SuspendThread(_t);
}

void Game::resumeGame(HANDLE _t)
{
	ResumeThread(_t);
}

void Game::login(Buffer buffer)
{
	system("cls");
	char m1[] = "New Game", m2[] = "Load Game", m3[] = "Setting";
	char *menu[] = { m1,m2,m3 };
	int pos = 0;
	const int y = 10;
	const int x = 55;
	bool flag = 0;
	drawLogo();
	drawBorder(10);
	while (flag == 0)
	{
		TextColor(14);
		for (int i = 0; i < 3; i++)
		{
			if (i == pos)
			{
				TextColor(12);
				GotoXY(x, y + i);
				cout << menu[i] ;
				TextColor(14);
			}
			else
			{
				GotoXY(x, y + i);
				cout << menu[i];
			}
		}
		while (1)
		{
			if (_kbhit())
			{
				char key = _getch();
				if (key == 'W' || key == 'w')
				{
					if (pos > 0)
						pos--;
					else
						pos = 2;
					break;
				}

				if (key == 'S' || key == 's')
				{
					if (pos < 2)
						pos++;
					else
						pos = 0;
					break;
				}

				if (key == 13)
				{
					switch (pos)
					{
					case 0:
					{
						system("cls");
						showMenuIngame();
						flag = 1;
						break;
					}
					case 1:
					{
						system("cls");
						if (!loadGame())
							login(buffer);
						showMenuIngame();
						flag = 1;
						break;
					}
					case 2:
					{
						flag = 1;
						Game::gameSetting(buffer);
						break;
					}
					}
					break;
				}
			}
		}
	}
}

int Game::pickLevel()
{
	system("cls");
	drawBorder(0);
	char s1[] = "Level 1", s2[] = "Level 2", s3[] = "Level 3", s4[] = "Level 4";
	char *sLevel[] = { s1,s2,s3,s4 };
	int pos = 0;
	const int y = 10;
	const int x = 55;
	int flag = 0;
	drawLogo();
	drawBorder(0);
	while (flag == 0)
	{
		TextColor(14);
		for (int i = 0; i < 4; i++)
		{
			if (i == pos)
			{
				TextColor(12);
				GotoXY(x, y + i);
				cout << sLevel[i];
				TextColor(14);
			}
			else
			{
				GotoXY(x, y + i);
				cout << sLevel[i];
			}
		}
		while (1)
		{
			if (_kbhit())
			{
				char key = _getch();
				if (key == 'W' || key == 'w')
				{
					if (pos > 0)
						pos--;
					else
						pos = 3;
					break;
				}

				if (key == 'S' || key == 's')
				{
					if (pos < 3)
						pos++;
					else
						pos = 0;
					break;
				}

				if (key == 13)
					return pos + 1;
			}
		}
	}
	return pos;
}

void Game::gameSetting(Buffer buffer)
{
	system("cls");
	char s1[] = "Level", s2[] = "Mute", s3[] = "Menu";
	char s2um[] = "Unmute";
	char *setting[] = { s1,s2,s3 };
	if (MUTE == 1)
		setting[1] = s2um;
	int pos = 0;
	const int y = 10;
	const int x = 55;
	int flag = 0;
	drawLogo();
	drawBorder(0);
	while (flag == 0)
	{
		TextColor(14);
		for (int i = 0; i < 3; i++)
		{
			if (i == pos)
			{
				TextColor(12);
				GotoXY(x, y + i);
				cout << setting[i];
				TextColor(14);
			}
			else
			{
				GotoXY(x, y + i);
				cout << setting[i];
			}
		}
		while (1)
		{
			if (_kbhit())
			{
				char key = _getch();
				if (key == 'W' || key == 'w')
				{
					if (pos > 0)
						pos--;
					else
						pos = 2;
					break;
				}

				if (key == 'S' || key == 's')
				{
					if (pos < 2)
						pos++;
					else
						pos = 0;
					break;
				}

				if (key == 13)
				{
					switch (pos)
					{
					case 0:
					{
						int n = pickLevel();
						_level = n;
						resetGame(_level, buffer);
						login(buffer);
						flag = 1;
						break;
					}
					case 1:
					{
						MUTE = !MUTE;
						flag = 1;
						login(buffer);
						break;
					}
					case 2:
					{
						flag = 1;
						Game::login(buffer);
						break;
					}
					}
					break;
				}
			}
		}
	}
}

bool Game::loadGame()
{
	string filename;
	TextColor(14);
	string dir = "Save/";
	GotoXY((GAME_LEFT_BOUND + GAME_RIGHT_BOUND) / 2 - 15, 3);
	cout << "Enter file name: ";
	getline(cin, filename);
	dir = dir + filename + ".dat";
	ifstream fi;
	fi.open(dir, ios::in | ios::binary);
	if (fi.fail())
	{
		GotoXY((GAME_LEFT_BOUND + GAME_RIGHT_BOUND) / 2 - 15, 4);
		cout << "NOT FOUND!";
		Sleep(1000);
		return false;
	}
	TextColor(7);
	delete[] _car;
	delete[] _truck;
	delete[] _bird;
	delete[] _dinosaur;
	fi.read(reinterpret_cast<char*>(&_level), sizeof(_level));
	_bird = new Bird[_level + 2];
	_dinosaur = new Dinosaur[_level + 2];
	_car = new Car[_level + 2];
	_truck = new Truck[_level + 2];
	int pX, pY, tTime;
	int rLight;
	fi.read(reinterpret_cast<char*>(&pX), sizeof(pX));
	fi.read(reinterpret_cast<char*>(&pY), sizeof(pY));
	fi.read(reinterpret_cast<char*>(&rLight), sizeof(rLight));
	fi.read(reinterpret_cast<char*>(&tTime), sizeof(tTime));

	_people.set(pX, pY);
	Light tLight;
	if (rLight == 0)
		tLight = red;
	else
		tLight = green;
	_light.set(tLight, tTime);
	int b, c;

	fi.read(reinterpret_cast<char*>(&b), sizeof(b));
	fi.read(reinterpret_cast<char*>(&c), sizeof(c));

	int animal_over = 0, vehicle_over = 0;

	for (int i = 0; i < _level + 2; i++)
	{
		int x_animals = b + i * (80 / (_level + 3));
		int x_vehicle = c - i * (80 / (_level + 3));

		if (x_animals >= GAME_RIGHT_BOUND - 2)
		{
			if (_bird[i - 1].X() > GAME_RIGHT_BOUND - 2 - (80 / (_level + 3)))
				x_animals = GAME_LEFT_BOUND + 1 + (80 / (_level + 3))*animal_over + ((80 / (_level + 3)) - (GAME_RIGHT_BOUND - 2 - _bird[i - 1].X()));
			else
				x_animals = _bird[i - 1].X() + (80 / (_level + 3));
			animal_over++;
		}
		if (x_vehicle <= GAME_LEFT_BOUND)
		{
			if (_car[i - 1].X() < GAME_LEFT_BOUND + (80 / (_level + 3)))
				x_vehicle = GAME_RIGHT_BOUND - 5 - (80 / (_level + 3))*vehicle_over - ((80 / (_level + 3)) - (_car[i - 1].X() - GAME_LEFT_BOUND - 1));
			else
				x_vehicle = _car[i - 1].X() - (80 / (_level + 3));
			vehicle_over++;
		}

		_bird[i].set(x_animals, Y_BIRD);
		_dinosaur[i].set(x_animals, Y_DINOSAUR);
		_car[i].set(x_vehicle, Y_CAR);
		_truck[i].set(x_vehicle, Y_TRUCK);
	}
	fi.close();
	return true;
}

void Game::saveGame()
{
	TextColor(14);
	ofstream fo;
	string filename;
	string dir = "Save/";
	GotoXY((GAME_LEFT_BOUND + GAME_RIGHT_BOUND) / 2 - 15, 3);
	cout << "Enter file name: ";
	getline(cin, filename);
	dir = dir + filename + ".dat";
	fo.open(dir, ios::out | ios::binary);
	TextColor(7);

	int pX = _people.X(), pY = _people.Y(), gL = _light.getLight(), gT = _light.getTime(), bX = _bird[0].X(), cX = _car[0].X();

	fo.write(reinterpret_cast<char*>(&_level), sizeof(_level));
	fo.write(reinterpret_cast<char*>(&pX), sizeof(pX));
	fo.write(reinterpret_cast<char*>(&pY), sizeof(pY));
	fo.write(reinterpret_cast<char*>(&gL), sizeof(gL));
	fo.write(reinterpret_cast<char*>(&gT), sizeof(gT));
	fo.write(reinterpret_cast<char*>(&bX), sizeof(bX));
	fo.write(reinterpret_cast<char*>(&cX), sizeof(cX));


	fo.close();
	GotoXY((GAME_LEFT_BOUND + GAME_RIGHT_BOUND) / 2 - 15, 3);
	cout << "                                                                      ";
	showMenuIngame();
	return;
}

void Game::drawBorder(int delay)
{
	const int x = 45;
	const int y = 8;
	TextColor(4);
	for (int i = x; i < x + 30; i++)
	{
		GotoXY(i, y);
		cout << char(220);
		Sleep(delay);
	}

	GotoXY(x + 29, y);
	cout << char(220);
	Sleep(delay);

	for (int i = y + 1; i < y + 7; i++)
	{
		GotoXY(x + 29, i);
		cout << char(219);
		Sleep(delay);
	}

	GotoXY(x + 29, y + 7);
	cout << char(223);
	Sleep(delay);

	for (int i = x + 29; i >= x; i--)
	{
		GotoXY(i, y + 7);
		cout << char(223);
		Sleep(delay);
	}

	GotoXY(x, y + 7);
	cout << char(223);
	Sleep(delay);

	for (int i = y + 6; i > y; i--)
	{
		GotoXY(x, i);
		cout << char(219);
		Sleep(delay);
	}

	GotoXY(x, y);
	cout << char(220);
	Sleep(delay);
	TextColor(7);
}

void Game::drawLogo()
{
	TextColor(4);
	GotoXY(20, 0);
	char l = 220, h = 223, f = 219, s = ' ';
	cout << f << h << l << s << l << h << h << l << s << s << l << h << l << s << s << f << h << h << l << s << s << s << l << h << h << s << f << h << l << s << l << h << h << l << s << s << s << l << h << h << l << s << s << s << l << h << h << l << s << f << s << f << h << l << s << s << f << s << l << h << h;
	GotoXY(20, 1);
	cout << f << h << l << s << h << l << l << h << s << f << h << h << h << f << s << f << l << l << h << s << s << s << h << l << l << s << f << h << l << s << h << l << l << h << s << h << l << l << h << s << s << s << h << l << l << h << s << s << s << f << s << f << s << s << h << l << f << s << h << l << l << f << h;
	TextColor(7);

}

