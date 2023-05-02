#ifndef __LOCATION_H
#define __LOCATION_H

#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include <fstream>
#include "conio.h"

#include <string>
#include <vector>
#include "dirent.h"
using namespace std;


#define SPEED 300
#define WIN 633 //105 // the number of bread crumbs on the board

#define HEART char(3)
#define BREAD_CRUMBS char(249)
#define PACKMAN char(2)
#define GHOST char(234)
#define BOARD char(219)
#define SPACE ' '

using std::cin;
using std::cout;
using std::endl;

enum { BEST = 1 , GOOD, NOVICE };
enum { UP, RIGHT, DOWN, LEFT, STAY, NOT_VALID, ESC = 27 };
enum { STRIKE, CRASH_BOARDER, NO_CRASH, TUNNEL, STRIKE_FRUIT_PACKMAN, STRIKE_FRUIT_GHOST };
enum { NEW_GAME = 1, INSTRUCTIONS = 8, EXIT = 9 };
enum { COL = 80, ROW = 25 }; 
enum { WITHOUT_COLOR = 1, WITH_COLOR = 2 };
enum { BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5, BROWN = 6, LIGHTGREY = 7, DARKGREY = 8, LIGHTBLUE = 9, LIGHTGREEN = 10, LIGHTCYAN = 11, LIGHTRED = 12, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15 };
enum { FRUIT_PROBABILITY = 50, FRUIT_LIVES = 4, FRUIT_KILL_STEPS = 80, FRUIT_KILL_FOREVER = 800 };
void gotoxy(int x, int y);

inline bool valid_ch(char ch)
{
	if (ch != ESC && ch != 'w' && ch != 'W' && ch != 'a' && ch != 'A' && ch != 'x' && ch != 'X' && ch != 'd' && ch != 'D' && ch != 's' && ch != 'S')
		return false;

	return true;
}

class Location {
private:
	int row, col;
	int tmp_row, tmp_col;

public:
	Location();
	Location(int _row, int _col);

	void setTmpRowCol(int _tmp_row, int _tmp_col);
	void setRowCol(int _row, int _col);
	void getRowCol(int& _row, int& _col)const;
	void getTmpRowCol(int& _row, int& _col)const;
	
};

#endif


