#ifndef __BOARD_H
#define __BOARD_H

#include "Location.h"

class Board 
{
private:
	char board[ROW][COL];
	bool pac_loc[ROW][COL];
	bool fruit_loc[ROW][COL];

	int color;
	int bar_row, bar_col;
	int board_rows, board_cols;

	Location packmanLoc;
	vector<vector<Location>> tunnels;

public:
	Board();

	void startNewBoard();
	char whatInBoard(int row, int col)const;
	void setBoardCell(int row, int col, char mark);

	char whatInPacLoc(int row, int col)const;
	void setPacLocCell(int row, int col);
	bool checkPacLocCell(int row, int col);
	void initPacLoc();

	void initFruitLoc();
	void setFruitLocCell(int row, int col);
	bool checkFruitLocCell(int row, int col);

	void updateBarLoc(int row, int col);
	void printBar(int life, int points);
	void printBoard()const;

	void setColor(int _color);

	void initSpot(int row, int col, char mark);
	void getBoard(string file_name, int& rows_num, int& cols_num);

	Location getPackmanLoction();
	void setPackmanLoction(Location _loc); 

	void getBoardSize(int& row_size, int& col_size);
	void setBoardSize(int row_size, int col_size);
	vector<vector<Location>> getTunnels();
	void setTunnels(vector<vector<Location>> _tunnels);
};
#endif