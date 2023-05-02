#ifndef __PACKMAN_H
#define __PACKMAN_H

#include "GameObjects.h"

class Board;
class GameObjects;

class Packman : public GameObjects 
{
private:
	Location start;
	int status;
	char ch;

public:
	Packman();
	void initLocation();
	void isInTunnel(vector<vector<Location>> tunnels, int& tmprow, int& tmpcol, int rows, int cols);

	void setStartLocation(int _row, int _col);
	void ifESC();
	int getDirectionFromPlayer(char ch)const;

	char getCh();
	void setCh(char _ch);
	int getStatus();
	void setStatus(int _status);

	virtual int move(Board& board)override;
	virtual int checkMove(Board& board)override;
	virtual void moveOnBoard(Board& board)override;
	void whereToMove();


};
#endif