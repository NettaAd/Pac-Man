#ifndef __FRUIT_H
#define __FRUIT_H

#include "GameObjects.h"

class Board;

class Fruit :public GameObjects
{
	int value;

public:
	Fruit();

	char getValue()const;
	void setValue(int _val);
	bool isInTunnel(vector<vector<Location>> tunnels, Location loc);

	virtual int move(Board& board)override;
	virtual int checkMove(Board& board)override;
	virtual void moveOnBoard(Board& board)override;

	void setFruitOnBoard(Board& board, int& is_fruit_alive);
};
#endif
