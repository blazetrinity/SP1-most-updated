#ifndef _PLAYER_H
#define _PLAYER_H

struct PlayerInfo
{
	COORD charLocation;
	int hp;
};

struct Health
{
	COORD charLocation;
};

//JOSH
void renderSelection();

//MALCOLM
void rendercharacter(int c);
void erasechar();

#endif