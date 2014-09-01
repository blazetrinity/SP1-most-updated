#include "game.h"
#include "fish.h"
#include "player.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

//MALCOLM
extern PlayerInfo player;

void rendercharacter(int c)
{
	switch (c)
	{
	case 1: 
		gotoXY(player.charLocation);
		if (player.charLocation.X == 17)
		{
			std::ifstream left;
			std::string asciileft;

			left.open ("ascii/left.txt");
			while (!left.eof())
			{
				gotoXY (player.charLocation);
				std::getline (left, asciileft);
				std::cout << asciileft;
				player.charLocation.Y += 1;
				if (player.charLocation.Y == 10)
				{
					player.charLocation.Y = 4;
				}
			}
		}
		else if (player.charLocation.X == 51)
		{
			std::ifstream right;
			std::string asciiright;

			right.open ("ascii/right.txt");
			while (!right.eof())
			{
				gotoXY (player.charLocation);
				std::getline (right, asciiright);
				std::cout << asciiright;
				player.charLocation.Y += 1;
				if (player.charLocation.Y == 10)
				{
					player.charLocation.Y = 4;
				}
			}
		}
		else
		{
			std::ifstream middle;
			std::string asciimid;

			middle.open ("ascii/middle.txt");
			while (!middle.eof())
			{ 
				gotoXY (player.charLocation);
				std::getline (middle, asciimid);
				std::cout << asciimid;
				player.charLocation.Y += 1;
				if (player.charLocation.Y == 10)
				{
					player.charLocation.Y = 4;
				}
			}
		}
		break;
	case 2: 
		gotoXY(player.charLocation);
		if (player.charLocation.X == 17)
		{
			std::ifstream left;
			std::string asciileft;

			left.open ("ascii/left2.txt");
			while (!left.eof())
			{
				gotoXY (player.charLocation);
				std::getline (left, asciileft);
				std::cout << asciileft;
				player.charLocation.Y += 1;
				if (player.charLocation.Y == 10)
				{
					player.charLocation.Y = 4;
				}
			}
		}
		else if (player.charLocation.X == 51)
		{
			std::ifstream right;
			std::string asciiright;

			right.open ("ascii/right2.txt");
			while (!right.eof())
			{
				gotoXY (player.charLocation);
				std::getline (right, asciiright);
				std::cout << asciiright;
				player.charLocation.Y += 1;
				if (player.charLocation.Y == 10)
				{
					player.charLocation.Y = 4;
				}
			}
		}
		else
		{
			std::ifstream middle;
			std::string asciimid;

			middle.open ("ascii/middle2.txt");
			while (!middle.eof())
			{ 
				gotoXY (player.charLocation);
				std::getline (middle, asciimid);
				std::cout << asciimid;
				player.charLocation.Y += 1;
				if (player.charLocation.Y == 10)
				{
					player.charLocation.Y = 4;
				}
			}
		}
		break;
	case 3: 
		gotoXY(player.charLocation);
		if (player.charLocation.X == 17)
		{
			std::ifstream left;
			std::string asciileft;

			left.open ("ascii/left3.txt");
			while (!left.eof())
			{
				gotoXY (player.charLocation);
				std::getline (left, asciileft);
				std::cout << asciileft;
				player.charLocation.Y += 1;
				if (player.charLocation.Y == 10)
				{
					player.charLocation.Y = 4;
				}
			}
		}
		else if (player.charLocation.X == 51)
		{
			std::ifstream right;
			std::string asciiright;

			right.open ("ascii/right3.txt");
			while (!right.eof())
			{
				gotoXY (player.charLocation);
				std::getline (right, asciiright);
				std::cout << asciiright;
				player.charLocation.Y += 1;
				if (player.charLocation.Y == 10)
				{
					player.charLocation.Y = 4;
				}
			}
		}
		else
		{
			std::ifstream middle;
			std::string asciimid;

			middle.open ("ascii/middle3.txt");
			while (!middle.eof())
			{ 
				gotoXY (player.charLocation);
				std::getline (middle, asciimid);
				std::cout << asciimid;
				player.charLocation.Y += 1;
				if (player.charLocation.Y == 11)
				{
					player.charLocation.Y = 4;
				}
			}
		}
		break;
	}
}

void erasechar()
{
	gotoXY(player.charLocation);

	if(player.charLocation.X==34)
	{
		std::ifstream emptymiddle;
		std::string asciiemptymiddle;

		emptymiddle.open ("ascii/emptymiddle.txt");
		while (!emptymiddle.eof())
		{
			gotoXY(player.charLocation);
			std::getline (emptymiddle, asciiemptymiddle);
			std::cout << asciiemptymiddle;
			player.charLocation.Y += 1;
			if (player.charLocation.Y == 10)
			{
				player.charLocation.Y = 4;
			}
		}
	}

	else
	{
		std::ifstream emptyside;
		std::string asciiemptyside;

		emptyside.open ("ascii/emptyside.txt");
		while (!emptyside.eof())
		{
			gotoXY(player.charLocation);
			std::getline (emptyside, asciiemptyside);
			std::cout << asciiemptyside;
			player.charLocation.Y += 1;
			if (player.charLocation.Y == 10)
			{
				player.charLocation.Y = 4;
			}
		}
	}
}