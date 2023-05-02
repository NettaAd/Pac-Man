#ifndef __GAME_H
#define __GAME_H

#include "Board.h"
#include "Ghost.h"
#include "Packman.h"
#include "Fruit.h"
#include "menu.h"

class Game 
{
private:
	bool end_game;
	int points, points_to_earn;
	int life, level;
	
	Menu menu;
	Board theGameBoard;
	Packman packman;
	vector<Ghost> ghosts;
	Fruit fruit;

public:
	Game();

	void init(string file_name);
	void initBoard();
	void makeTunnels();

	void start();

	void playNewGame(int if_color);
	void beforeFirstMove(int& status);
	void afterFirstMove(int& status, int& move_counter, char& ch, int& is_fruit_alive);

	void checkWin();
	void checkEndGame();
};

#endif 
