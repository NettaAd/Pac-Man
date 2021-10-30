#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <iostream>
#include "conio.h"

using namespace std;
#define ROW_SIZE 16
#define COL_SIZE 60
#define TUNNEL_SIZE 6
#define OBSTACLE_WIDTH 2
#define ROW_IN_BORD 11
#define COL_IN_BORD 11
#define ESC 27   // Escape Key
#define PACMAN 'C'

class Point {
public:
	int x;
	int y;

	Point(int newX, int newY) { x = newX; y = newY; };
};

void printBoard();
void printLine();
void printTunnels();
void printObstacles();
void playGame();
void gotoxy(int, int); // prototype
void clrscr(); // prototype
bool isPackmanCrashBorders(int x, int y);


// function definition -- requires windows.h
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
// function definition -- requires process.h
void clrscr()
{
	system("cls");
}

void playGame()
{
	char direction;
	int x = 2, y = 2;
	bool validD = true;

	gotoxy(x, y);
	cout << PACMAN;

	direction = _getch();

	/*****************************    chack if the input is valid    ****************************/



	/* Once the user selects move direction (using the keys, as listed below) */

	while (validD)
	{
		/********************************   make a move   ********************************/
		Sleep(300);

		if (_kbhit())
			direction = _getch();

		/*  the pacman will continue to move in this direction even if the user
			doesn’t press any key */

		if (direction == 'w' || direction == 'W') // UP
		{
			if (isPackmanCrashBorders(x, y - 1))
				continue;
			gotoxy(x, y);
			cout << " ";
			y--;
			gotoxy(x, y);
			cout << PACMAN;
		}
		else if (direction == 'x' || direction == 'X') // DOWN
		{
			if (isPackmanCrashBorders(x, y + 1))
				continue;
			gotoxy(x, y);
			cout << " ";
			y++;
			gotoxy(x, y);
			cout << PACMAN;
		}
		else if (direction == 'a' || direction == 'A') // LEFT
		{
			if (isPackmanCrashBorders(x - 1, y))
				continue;
			gotoxy(x, y);
			cout << " ";
			x--;
			gotoxy(x, y);
			cout << PACMAN;
		}
		else if (direction == 'd' || direction == 'D') // RIGHT
		{
			if (isPackmanCrashBorders(x + 1, y))
				continue;
			gotoxy(x, y);
			cout << " ";
			x++;
			gotoxy(x, y);
			cout << PACMAN;
		}

		/* as long as the pacman doesn’t hit a wall and the “STAY” key was not pressed */
		else if (direction == 's' || direction == 'S') // STAY
			continue;
	}
}
bool isPackmanCrashBorders(int x, int y)
{
	/* chack if the packman hit a board border */
	if (x == 0 || x == ROW_SIZE || y == 0 || y == COL_SIZE)
	{
		return true;
	}
	/* chack if the packman hit a inner border */

	return false;
}

void printBoard()
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		if (i == 0)
			printLine();
		else if (i != ROW_SIZE / 2) //not on tunnel
		{
			gotoxy(0, i);
			cout << "#";
			gotoxy(COL_SIZE - 1, i);
			cout << "#";
		}
	}
	gotoxy(0, ROW_SIZE);
	printLine();
	printTunnels();
	printObstacles();
	gotoxy(100, 100);
}
void printTunnels()
{
	//left tunnel
	gotoxy(1, ROW_SIZE / 2 - 1);
	for (int i = 1; i < TUNNEL_SIZE; i++)
		cout << "#";
	gotoxy(1, ROW_SIZE / 2 + 1);
	for (int i = 1; i < TUNNEL_SIZE; i++)
		cout << "#";

	//right tuunel
	gotoxy(COL_SIZE - TUNNEL_SIZE, ROW_SIZE / 2 - 1);
	for (int i = 1; i < TUNNEL_SIZE; i++)
		cout << "#";
	gotoxy(COL_SIZE - TUNNEL_SIZE, ROW_SIZE / 2 + 1);
	for (int i = 1; i < TUNNEL_SIZE; i++)
		cout << "#";

	//top tunnel
	for (int i = 1; i < TUNNEL_SIZE / 2; i++)
	{
		gotoxy(COL_SIZE / 2 - 1, i);
		cout << "#";
		gotoxy(COL_SIZE / 2 + 1, i);
		cout << "#";
	}

	//bottom tunnel
	for (int i = 1; i < TUNNEL_SIZE / 2; i++)
	{
		gotoxy(COL_SIZE / 2 - 1, ROW_SIZE - i);
		cout << "#";
		gotoxy(COL_SIZE / 2 + 1, ROW_SIZE - i);
		cout << "#";
	}
}
void printLine()
{
	for (int i = 0; i < COL_SIZE; i++)
		cout << "#";
	gotoxy(COL_SIZE / 2, 0);
	cout << " ";
	gotoxy(COL_SIZE / 2, ROW_SIZE);
	cout << " ";
}
void printObstacles()
{
	int shift_from_left = COL_SIZE / 4 + OBSTACLE_WIDTH;
	//print 1
	for (int i = 0; i < ROW_SIZE / 2; i++)
	{
		if (i == 0 || i == ROW_SIZE / 2 - 1)
		{
			gotoxy(shift_from_left, ROW_SIZE / 4 + i);
			for (int j = 0; j < OBSTACLE_WIDTH; j++)
				cout << "#";
		}
		gotoxy(shift_from_left, ROW_SIZE / 4 + i);
		cout << "#";
		gotoxy((shift_from_left)+(OBSTACLE_WIDTH), ROW_SIZE / 4 + i);
		cout << "#";
	}
	//print first 0
	for (int i = 0; i < ROW_SIZE / 2; i++)
	{
		if (i == 0 || i == ROW_SIZE / 2 - 1)
		{
			gotoxy((shift_from_left)+(4 * OBSTACLE_WIDTH), ROW_SIZE / 4 + i);
			for (int j = 0; j < 3 * OBSTACLE_WIDTH; j++)
				cout << "#";
		}
		gotoxy((shift_from_left)+(4 * OBSTACLE_WIDTH), ROW_SIZE / 4 + i);
		cout << "#";
		gotoxy((shift_from_left)+(4 * OBSTACLE_WIDTH) + (3 * OBSTACLE_WIDTH), ROW_SIZE / 4 + i);
		cout << "#";
	}
	//print second 0
	for (int i = 0; i < ROW_SIZE / 2; i++)
	{
		if (i == 0 || i == ROW_SIZE / 2 - 1)
		{
			gotoxy((shift_from_left)+(10 * OBSTACLE_WIDTH), ROW_SIZE / 4 + i);
			for (int j = 0; j < 3 * OBSTACLE_WIDTH; j++)
				cout << "#";
		}
		gotoxy((shift_from_left)+(10 * OBSTACLE_WIDTH), ROW_SIZE / 4 + i);
		cout << "#";
		gotoxy((shift_from_left)+(10 * OBSTACLE_WIDTH) + (3 * OBSTACLE_WIDTH), ROW_SIZE / 4 + i);
		cout << "#";
	}
}

void main() {
	printBoard();
	playGame();
	gotoxy(20, 20);
}
