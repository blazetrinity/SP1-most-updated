#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <vector>
#include <string>
#include <ctime>

using std::vector;
using std::ifstream;
using std::ofstream;
extern StopWatch g_timer;
extern bool g_quitGame;
extern bool g_pause;
using std::string;

enum KEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_RETURN,
    K_COUNT,
	K_PLAY,
	K_BACK,
};

enum STATES
{
	S_MAINSCREEN = 1,
	S_INSTRUCTIONS,
	S_START,
	S_GAMEOVER,
	S_SCORE,
	S_CREDITS,
	S_SELECTCHAR,
};

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

//JOSH RENDERER
void renderGame();
void renderMenu();
void renderScore();
void renderInstructions();
void renderCredits();
void renderGameover();

//HONG XI RENDERER
void renderMap();

#endif // _GAME_H