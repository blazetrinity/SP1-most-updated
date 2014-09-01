// This is the main file for the game logic and function
//
//
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
using std::string;
using std::ifstream;

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD squidLocation;
COORD testLocation;
COORD treeLocation;
COORD consoleSize;

//MALCOLM
vector<fishInfo> fishvector;
double canspawn=50.000;
double canmove=0.000;
double canmove2=0.000;
double canmove3=0.000;
double typetime=0.00;
double raremultiplier=0.00;
double multipliertime=0.00;
int score=0;
PlayerInfo player;
Health health;
const WORD colors[] = {0x00,0x07,0x06,0x04,0x09};
const int c_playerlimitmin = 17;
const int c_playerlimitmax = 51;
int multiplier=1;
bool b_multiplier=false;

//STATES
STATES state = S_MAINSCREEN;

//WAYNE
int hscore = 0;
int playerScore = 0;

//JOSH
const int c_lowerlimit = 17;
const int c_upperlimit = 25;
const int c_startlocation = 17;
const int c_instructlocation = 19;
const int c_scorelocation = 21;
const int c_creditslocation = 23;
const int c_quitlocation = 25;
const int c_character1 = 16;
const int c_character2 = 37;
const int c_character3 = 60;
int g_choice = 0;
COORD selectLocation;
COORD char1Location;
COORD char2Location;
COORD char3Location;
COORD cursorLocation;
COORD gameoverLocation;

//HONG XI
COORD mapLocation;
COORD creditsLocation;

void init()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"SP1 Framework");

	// Sets the console size, this is the biggest so far.
	setConsoleSize(79, 28);

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	//JOSH
	squidLocation.X = 50;
	squidLocation.Y = 17;

	testLocation.X = 0;
	testLocation.Y = 2;

	treeLocation.X = 55;
	treeLocation.Y = 0;

	selectLocation.X = 18;
	selectLocation.Y = 15;

	char1Location.X = 15;
	char1Location.Y = 5;

	char2Location.X = 37;
	char2Location.Y = 5;

	char3Location.X = 59;
	char3Location.Y = 4;

	cursorLocation.X = 16;
	cursorLocation.Y = 12;

	gameoverLocation.X = 0;
	gameoverLocation.Y = 2;

	//MALCOLM
	player.charLocation.X = 34;
	player.charLocation.Y = 4;
	player.hp = 3;

	health.charLocation.X=8;
	health.charLocation.Y=2;

	//HONG XI
	mapLocation.X = 0;
	mapLocation.Y = 8;

	creditsLocation.X = 0;
	creditsLocation.Y = 2;


	elapsedTime = 0.0;
}

void shutdown()
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
	keyPressed[K_UP] = isKeyPressed(VK_UP);
	keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
	keyPressed[K_PLAY] = isKeyPressed(0x50); //P key
	keyPressed[K_BACK] = isKeyPressed(VK_BACK); //Backspace
}

void update(double dt)
{
	// get the delta time
	elapsedTime += dt;
	deltaTime = dt;
	canspawn += dt;
	canmove += dt;
	canmove2 +=dt;
	canmove3 +=dt;
	typetime +=dt;
	raremultiplier +=dt;
	if(b_multiplier==true)
	{
		multipliertime +=dt;
	}

	// Updating the location of the character based on the key press
	if (keyPressed[K_UP] && squidLocation.Y > c_lowerlimit)
	{
		Beep(1440, 30);
		gotoXY(squidLocation);
		cout << "      ";
		squidLocation.Y -= 2; 
	}

	if ((keyPressed[K_LEFT] && player.charLocation.X > c_playerlimitmin) && state == S_START)
	{
		erasechar();
		Beep(1440, 30);
		player.charLocation.X-=17; 
	}

	if (keyPressed[K_DOWN] && squidLocation.Y < c_upperlimit)
	{
		Beep(1440, 30);
		gotoXY(squidLocation);
		cout << "      ";
		squidLocation.Y += 2;
	}

	if ((keyPressed[K_RIGHT] && player.charLocation.X < c_playerlimitmax) && state == S_START)
	{
		erasechar();
		Beep(1440, 30);
		player.charLocation.X += 17; 
	}

	if((keyPressed[K_RETURN] && squidLocation.Y == c_startlocation) && state == S_MAINSCREEN)
	{
		Beep(1440, 30);
		cls();
		state = S_SELECTCHAR;
	}

	if((keyPressed[K_RETURN] && squidLocation.Y == c_instructlocation) && state == S_MAINSCREEN)
	{
		Beep(1440, 30);
		cls();
		state = S_INSTRUCTIONS;
	}

	if((keyPressed[K_RETURN] && squidLocation.Y == c_scorelocation) && state == S_MAINSCREEN)
	{
		Beep(1440, 30);
		//state = S_SCORE; 
		cout << " WAYNE DIDNT DO SHIT" << endl;
	}

	if((keyPressed[K_RETURN] && squidLocation.Y == c_creditslocation) && state == S_MAINSCREEN)
	{
		cls();
		state = S_CREDITS;
	}

	// quits the game if player hits the escape key
	if ((keyPressed[K_RETURN] && squidLocation.Y == c_quitlocation) && state == S_MAINSCREEN)
	{
		g_quitGame = true;
	}

	if (keyPressed[K_ESCAPE])
	{
		g_quitGame = true;
	}

	if (keyPressed[K_BACK] && (state == S_INSTRUCTIONS || state == S_CREDITS))
	{
		cls();
		state = S_MAINSCREEN;
	}
	//////////////////////////////////      JOSH      ///////////////////////////////////////////
	if ((keyPressed[K_RIGHT] && cursorLocation.X == c_character1) && state == S_SELECTCHAR)
	{
		gotoXY(cursorLocation);
		cout << "    ";
		cursorLocation.X += 21; 
	}
	else if((keyPressed[K_RIGHT] && cursorLocation.X == c_character2) && state == S_SELECTCHAR)
	{
		gotoXY(cursorLocation);
		cout << "       ";
		cursorLocation.X += 23; 
	}

	if ((keyPressed[K_LEFT] && cursorLocation.X == c_character2) && state == S_SELECTCHAR)
	{
		gotoXY(cursorLocation);
		cout << "       ";
		cursorLocation.X -= 21; 
	}

	if ((keyPressed[K_LEFT] && cursorLocation.X > c_character1) && state == S_SELECTCHAR)
	{
		gotoXY(cursorLocation);
		cout << "       ";
		cursorLocation.X -= 23; 
	}

	if((keyPressed[K_PLAY] && cursorLocation.X == c_character2) && state == S_SELECTCHAR)
	{
		g_choice = 2;
		cls();
		renderMap();
		state = S_START;
	}
	else if((keyPressed[K_PLAY] && cursorLocation.X == c_character3) && state == S_SELECTCHAR)
	{
		g_choice = 3;
		cls();
		renderMap();
		state = S_START;
	}
	else if((keyPressed[K_PLAY] && cursorLocation.X == c_character1) && state == S_SELECTCHAR)
	{
		g_choice = 1;
		cls();
		renderMap();
		state = S_START;
	}
	//////////////////////////////////////////////////////////////////////////////////////////

	switch(state)
	{
	case S_MAINSCREEN:
		renderMenu();
		break;
	case S_INSTRUCTIONS:
		renderInstructions();
		cout << endl;
		break;
	case S_START:
		//renderMap();
		renderGame();
		break;
	case S_SCORE:
		renderScore();
		break;
	case S_CREDITS:
		renderCredits();
		break;
	case S_SELECTCHAR:
		renderSelection();
		break;
	case S_GAMEOVER:
		renderGameover();
		break;
	}

	if(player.hp == 0)
	{
		player.hp = 1;
		cls();
		state = S_GAMEOVER;
	}
}

void renderMenu()
{
	gotoXY(testLocation);
	colour(0x7);
	std::ifstream title;
	std::string titleascii;

	title.open ("Ascii/title.txt");
	while(!title.eof())
	{
		gotoXY(testLocation);
		std::getline(title, titleascii);
		cout << titleascii;
		testLocation.Y += 1;
		if(testLocation.Y == 10)
		{
			testLocation.Y = 2;
		}

	}

	gotoXY(treeLocation);
	colour(0x7);
	std::ifstream tree;
	std::string treeascii;

	tree.open ("Ascii/Tree2.txt");
	while(!tree.eof())
	{
		gotoXY(treeLocation);
		std::getline(tree, treeascii);
		cout << treeascii;
		treeLocation.Y += 1;
		if(treeLocation.Y == 13)
		{
			treeLocation.Y = 0;
		}

	}

	for(int i = 0; i < consoleSize.X; i++)
	{
		cout << (char)176;
	}

	gotoXY(33,17);
	colour(0x7);
	cout << "1) Start Game";
	gotoXY(33,19);
	cout << "2) Instructions";
	gotoXY(33,21);
	cout << "3) Highscores";
	gotoXY(33,23);
	cout << "4) Credits";
	gotoXY(33,25);
	cout << "5) Quit";

	// render squid cursor
	gotoXY(squidLocation);
	colour(0x07);
	cout << "<^))<3";
}

void renderGame()
{	
	rendercharacter(g_choice);

	int prevhp=player.hp;
	const string piece="><>";
	const int maxfish=6;
	const double spawntimer=50.00;
	const double raretimer=65.00;
	const double superraretimer=75.00;
	const double multiplierlimit=150.0;
	bool position1=false;
	bool position2=false;
	bool position3=false;

	//create fish
	if(canspawn>=spawntimer && ::fishvector.size()<maxfish)
	{
		srand(time(NULL));
		canspawn=0.0;
		fishInfo fish;
		::fishvector.push_back(fish);
		int i=(::fishvector.size())-1;
		int place = 0;

		//rare fish spawn
		if(typetime >=raretimer)
		{
			typetime=0.0;
			int type = 0;

			if(raremultiplier >= superraretimer )
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
			case 1: ::fishvector[i].type=1;
				break;
			case 2: ::fishvector[i].type=2;
				break;
			case 3: ::fishvector[i].type=3;
				break;
			case 4: ::fishvector[i].type=4;
				break;
			}
		}

		else
		{
			::fishvector[i].type=1;
		}

		//overlap spawn prevention
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
				place=3;
			}

			else if(position3==true)
			{
				place=2;
			}
			else
			{
				place=rand()%3+2;
			}
		}

		else if(position2==true)
		{
			if(position1==true)
			{
				place=3;
			}

			else if(position3==true)
			{
				place=1;
			}
			else
			{
				place=rand()%3+2;
				if(place==2)
				{
					place=3;
				}
			}
		}

		else if(position3==true)
		{
			if(position1==true)
			{
				place=2;
			}

			else if(position2==true)
			{
				place=1;
			}
			else
			{
				place=rand()%2+1;
			}
		}

		else
		{
			place=rand()%3+1;
		}

		switch(place)
		{
		case 1: ::fishvector[i].position = 1;
			::fishvector[i].x = 17;
			::fishvector[i].y = 31;
			break;
		case 2: ::fishvector[i].position = 2;
			::fishvector[i].x = 37;
			::fishvector[i].y = 26;
			break;
		case 3: ::fishvector[i].position = 3;
			::fishvector[i].x = 37;
			::fishvector[i].y = 31;
			break;
		}
		gotoXY(::fishvector[i].x,::fishvector[i].y);
		colour(colors[::fishvector[i].type]);
		std::cout << piece;
		colour(colors[1]);
	}

	//delete the fish
	for(int p=0;p<=((::fishvector.size())-1);p++)
	{
		const string del="   ";

		//delete current fish location
		gotoXY(::fishvector[p].x,::fishvector[p].y);
		std::cout << del;
	}

	movefish();

	//print the fish
	for(int e=0;e<::fishvector.size();e++)
	{
		gotoXY(::fishvector[e].x,::fishvector[e].y);
		colour(colors[::fishvector[e].type]);
		std::cout << piece;
		colour(colors[1]);
	}

	//check location of the character for score
	for(int c=0;c<::fishvector.size();c++)
	{
		if(::fishvector[c].y==6)
		{
			if(player.charLocation.X==17 && ::fishvector[c].x==17 || player.charLocation.X==34 && ::fishvector[c].x==37 || player.charLocation.X==51 && ::fishvector[c].x==60)
			{
				switch(::fishvector[c].type)//score
				{
				case 1: score += (1 * multiplier);
					break;
				case 2: score += (5 * multiplier);
					break;
				case 3: score += (1 * multiplier); 
					if(player.hp<6)
					{
						player.hp++;
					}
					break;
				case 4: multiplier=multiplier*2;
						score += (1 * multiplier);
						b_multiplier=true;
					break;
				}	
			}

			else
			{
				player.hp--;
			}
			replacefish(c);
		}
	}

	// render time taken to calculate this frame
	gotoXY(70, 0);
	std::cout << 1.0 / deltaTime << "fps" << std::endl;

	gotoXY(0, 0);
	std::cout << elapsedTime << "secs" << std::endl;

	//player health
	gotoXY(0,2);
	std::cout << "Health: ";

	//deleting hearts
	for(int k=0;k<prevhp;k++)
	{
		gotoXY(health.charLocation.X, health.charLocation.Y);
		std::cout << " ";
		health.charLocation.X++;
	}
	health.charLocation.X=8;

	//printing hearts
	for(int j=0; j<player.hp; j++)
	{
		gotoXY (health.charLocation.X, health.charLocation.Y);
		std::cout << (char)3;
		health.charLocation.X++;
	}
	health.charLocation.X=8;

	//score
	gotoXY(0,1);
	std::cout << "Score: " << score;

	if(multipliertime>=multiplierlimit)
	{
		multipliertime=0.00;
		b_multiplier=false;
		multiplier=multiplier/2;
	}
}

void renderScore()
{
	string data;
	ifstream inData("highscore.txt");

	if (inData.is_open())
	{
		while (getline(inData, data))
		{
			hscore = std::stoi(data);
			if (playerScore >= hscore)
			{
				hscore = playerScore;
				ofstream outData("highscore.txt");
				if (outData.is_open())
				{
					outData << hscore;
					outData.close();
					cout << "New Highscore!" << endl;
				}
			}
			gotoXY(27, 0);
			cout << "Players Highscore: " << hscore << endl;
			cout << "Player's Score: " << playerScore << endl;
		}
		inData.close();
	}
	else
	{
		ofstream outData("highscore.txt");
		if (outData.is_open())
		{
			outData << hscore;
			outData.close();
			cout << "Completed";
		}
	}
}	

void renderSelection()
{
	gotoXY(char1Location);
	colour(0x7);
	std::ifstream char1;
	std::string char1ascii;

	char1.open ("Ascii/middle.txt");
	while(!char1.eof())
	{
		gotoXY(char1Location);
		std::getline(char1, char1ascii);
		cout << char1ascii;
		char1Location.Y += 1;
		if (char1Location.Y == 11)
		{
			char1Location.Y = 5;
		}
	}

	gotoXY(char2Location);
	colour(0x7);
	std::ifstream char2;
	std::string char2ascii;

	char2.open ("Ascii/middle2.txt");
	while(!char2.eof())
	{
		gotoXY(char2Location);
		std::getline(char2, char2ascii);
		cout << char2ascii;
		char2Location.Y += 1;
		if (char2Location.Y == 11)
		{
			char2Location.Y = 5;
		}
	}

	gotoXY(char3Location);
	colour(0x7);
	std::ifstream char3;
	std::string char3ascii;

	char3.open ("Ascii/middle3.txt");
	while(!char3.eof())
	{
		gotoXY(char3Location);
		std::getline(char3, char3ascii);
		cout << char3ascii;
		char3Location.Y += 1;
		if (char3Location.Y == 11)
		{
			char3Location.Y = 4;
		}
	}

	//select cursor
	gotoXY(cursorLocation);
	colour(0x07);
	if(cursorLocation.X == 16)
	{
	    cout << "Josh";
	}
	else if (cursorLocation.X == 37)
	{
		cout << "Hong Xi";
	}
	else if (cursorLocation.X == 60)
	{
		cout << "Malcolm";
	}

	gotoXY(selectLocation);
	colour(0x07);
	cout << "Please select a character and press P to play!" << endl;
}

void renderInstructions()
{
	gotoXY(testLocation);
	colour(0x7);
	std::ifstream instructions;
	std::string instructionsascii;

	instructions.open ("Ascii/Instructions.txt");
	while(!instructions.eof())
	{

		gotoXY(testLocation);
		std::getline(instructions, instructionsascii);
		cout << instructionsascii;
		testLocation.Y += 1;
		if(testLocation.Y == 22)
		{
			testLocation.Y = 2;
		}

	}

	cout << endl;

	for(int i = 0; i < consoleSize.X; i++)
	{
		cout << (char)176;
	}
}

void renderMap()
{
	gotoXY(mapLocation);
	ifstream map;
	string asciimap;

	map.open ("ascii/map.txt");
	while (!map.eof())
	{
		gotoXY(mapLocation);
		getline(map, asciimap);
		cout << asciimap;
		mapLocation.Y += 1;
		if (mapLocation.Y == 12)
		{
			mapLocation.Y = 8;
		}
		//asciimap.push_back (map.get());
	}
}

void renderGameover()
{
	gotoXY(gameoverLocation);
	colour(0x07);
	ifstream gameover;
	string asciigameover;

	gameover.open("ascii/gameover.txt");
	while(!gameover.eof())
	{
		gotoXY(gameoverLocation);
		getline(gameover, asciigameover);
		cout << asciigameover;
		gameoverLocation.Y += 1;
		if (gameoverLocation.Y == 13)
		{
			gameoverLocation.Y = 2;
		}
	}

}

void renderCredits() //18
{
	gotoXY(creditsLocation);
	colour(0x07);
	ifstream credits;
	string asciicredits;

	credits.open("ascii/credits.txt");
	while(!credits.eof())
	{
		gotoXY(creditsLocation);
		getline(credits, asciicredits);
		cout << asciicredits;
		creditsLocation.Y += 1;
		if(creditsLocation.Y == 21)
		{
			creditsLocation.Y = 2;
		}
		if(creditsLocation.Y == 10)
		{
			cout << endl;
			for(int i = 0; i < consoleSize.X; i++)
			{
				cout << (char)176;
			}
		}
	}
}