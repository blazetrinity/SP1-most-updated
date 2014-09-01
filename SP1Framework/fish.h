#ifndef _FISH_H
#define _FISH_H

struct fishInfo
{
	int position;
	int x;
	int y;
	int type;
};

//MALCOLM
void movefish();
void replacefish(int);

#endif