#include "Location.h"

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

Location::Location() { row = col = tmp_row = tmp_col = 0; }
Location::Location(int _row, int _col) : row(_row), col(_col), tmp_row(_row), tmp_col(_col) {}

void Location::setTmpRowCol(int _tmp_row, int _tmp_col) { tmp_row = _tmp_row; tmp_col = _tmp_col; }
void Location::setRowCol(int _row, int _col) { row = _row; col = _col; }

void Location::getRowCol(int& _row, int& _col)const { _row = row;	_col = col; }
void Location::getTmpRowCol(int& _row, int& _col)const { _row = tmp_row;	_col = tmp_col; }