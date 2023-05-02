#ifndef __GAME_OBJECT_h
#define __GAME_OBJECT_h

#include "Board.h"

class GameObjects
{
private:
	Location loc;
	int direction;

public:
	GameObjects();

	void getLocation(int& _row, int& _col)const; 
	void getTmpLocation(int& _row, int& _col)const; 
	void setLocation(int row, int col); 
	void setTmpLocation(int tmp_row, int tmp_col); 

	bool compLoc(Location one, Location two);

	int getDirection()const;
	void setDirection(int new_direction);

	void changeLocation(int direction);

	virtual int move(Board& board) = 0 ;
	virtual int checkMove(Board& board) = 0;
	virtual void moveOnBoard(Board& board) = 0;

	bool insideBoard(int board_rows, int board_cols, int tmp_row, int tmp_col);
	
};


#endif 
