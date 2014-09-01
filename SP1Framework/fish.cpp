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

extern vector<fishInfo> fishvector;
extern double canspawn;
extern double canmove;
extern double canmove2;
extern double canmove3;
extern double typetime;
extern double raremultiplier;
extern int score;
extern Health health;
//extern const WORD colors[];
const WORD colors[] = {0x00,0x07,0x06,0x04,0x09};
extern const int c_playerlimitmin;
extern const int c_playerlimitmax;

void movefish()
{
	if(canmove>1.50)
	{
		canmove=0.00;
		for(int o=0;o<::fishvector.size();o++)
		{
			if(::fishvector[o].position==1)
			{
				::fishvector[o].y-=5;
			}
		}

	}
	if(canmove2>1.25)
	{
		canmove2=0.0;
		for(int y=0;y<fishvector.size();y++)
		{
			if(::fishvector[y].position==2)
			{
				::fishvector[y].y-=5;
			}
		}
	}
	if(canmove3>1.75)
	{
		canmove3=0.0;
		for(int z=0;z<fishvector.size();z++)
		{
			if(::fishvector[z].x==37 && ::fishvector[z].y==31)
			{
				::fishvector[z].x=60;
			}
			else if(::fishvector[z].position== 3)
			{
				::fishvector[z].y-=5;
			}
		}
	}
}

void replacefish(int r)
{
	srand(time(NULL));
	const string del="   ";
	const string piece="><>";
	double superraretimer=75.00;
	int replace =0;

	bool position1=false;
	bool position2=false;
	bool position3=false;

	//delete the fish at the top
	gotoXY(::fishvector[r].x,::fishvector[r].y);
	std::cout << del;
	gotoXY(::fishvector[r].x,11);
	std::cout << "___";

	//overlap respawn prevention
	for(int t=0;t<::fishvector.size();t++)
	{
		if(::fishvector[t].x==17 && ::fishvector[t].y==31)
		{
			position1=true;
		}

		else if(::fishvector[t].x==37 && ::fishvector[t].y==26)
		{
			position2=true;
		}

		else if(::fishvector[t].x==37 && ::fishvector[t].y==31)
		{
			position3=true;
		}
	}

	if(position1==true)
	{
		if(position2==true)
		{
			replace=3;
		}

		else if(position3==true)
		{
			replace=2;
		}
		else
		{
			replace=rand()%3+2;
		}
	}

	else if(position2==true)
	{
		if(position1==true)
		{
			replace=3;
		}

		else if(position3==true)
		{
			replace=1;
		}
		else
		{
			replace=rand()%3+2;
			if(replace==2)
			{
				replace=3;
			}
		}
	}

	else if(position3==true)
	{
		if(position1==true)
		{
			replace=2;
		}

		else if(position2==true)
		{
			replace=1;
		}
		else
		{
			replace=rand()%2+1;
		}
	}

	else
	{
		replace=rand()%3+1;
	}

	switch(replace)		
	{
	case 1: ::fishvector[r].position = 1;
		::fishvector[r].x = 17;
		::fishvector[r].y = 31;
		break;
	case 2: ::fishvector[r].position = 2;
		::fishvector[r].x = 37;
		::fishvector[r].y = 26;	
		break;
	case 3: ::fishvector[r].position = 3;
		::fishvector[r].x = 37;
		::fishvector[r].y = 31;
		break;
	}		


	//rare respawn
	if(typetime >=13.00)
	{
		typetime=0.0;
		int type = 0;

		if(raremultiplier >=superraretimer)
		{
			type=rand()%4+1;
			raremultiplier=0.00;
		}
		
		else
		{
			type=rand()%3+1;
		}

		switch(type)
		{
		case 1: ::fishvector[r].type=1;
			break;
		case 2: ::fishvector[r].type=2;
			break;
		case 3: ::fishvector[r].type=3;
			break;
		case 4: ::fishvector[r].type=4;
			break;
		}
	}

	else
	{
		::fishvector[r].type=1;
	}

	//print at reset position
	gotoXY(::fishvector[r].x,::fishvector[r].y);
	colour(colors[::fishvector[r].type]);
	std::cout << piece;
	colour(colors[1]);
}