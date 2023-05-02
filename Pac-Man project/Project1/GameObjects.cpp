#include "GameObjects.h"

GameObjects::GameObjects(): direction(NOT_VALID), loc() {}

void GameObjects::getLocation(int& _row, int& _col)const { loc.getRowCol(_row, _col); }
void GameObjects::getTmpLocation(int& _row, int& _col)const { loc.getTmpRowCol(_row, _col); }
void GameObjects::setLocation(int row, int col) { loc.setRowCol(row, col); }
void GameObjects::setTmpLocation(int tmp_row, int tmp_col) { loc.setTmpRowCol(tmp_row, tmp_col); }
bool GameObjects::compLoc(Location one, Location two)
{
	int row1, col1, row2, col2;
	one.getRowCol(row1, col1);
	two.getRowCol(row2, col2);
	if (row1 == row2 && col2 == col1)
		return true;
	else
		return false;
}
void GameObjects::changeLocation(int direction)
{
	int tmp_row, tmp_col, row, col;

	getLocation(row, col);
	getTmpLocation(tmp_row, tmp_col);

	switch (direction)
	{
	case UP:
		tmp_row--;
		break;
	case RIGHT:
		tmp_col++;
		break;
	case DOWN:
		tmp_row++;
		break;
	case LEFT:
		tmp_col--;
		break;
	default:
		break;
	}

	setTmpLocation(tmp_row, tmp_col);
}
int GameObjects::getDirection()const { return direction; }
void GameObjects::setDirection(int new_direction) { direction = new_direction; }
bool GameObjects::insideBoard(int board_rows, int board_cols, int tmp_row, int tmp_col)
{
	if (tmp_row >= 0 && tmp_row <= board_rows - 1)
		if (tmp_col >= 0 && tmp_col <= board_cols - 1)
			return true;

	return false;
}

