#ifndef __GHOST_H
#define __GHOST_H

#include "GameObjects.h"

class Game;

class Ghost :public GameObjects 
{
private:
	Location start;
	int steps_counter_race, steps_counter_rand;
	int level;

public:
	Ghost(Location _loc);

	void initLocation();

	bool isInTunnel(vector<vector<Location>> _tunnels, Location loc);
	float distance(int x1, int y1, int x2, int y2);
	vector<float> findMinimumDistance(float x1, float x2, float x3, float x4);
	vector<int> findPackmanDirecion(int packman_row, int packman_col);

	void setLevel(int _level);

	void setRaceStepsCounter(int _counter);
	int getRaceStepsCounter();

	void setRandStepsCounter(int _counter);
	int getRandStepsCounter();

	virtual int move(Board& board)override;
	virtual int checkMove(Board& board)override;
	virtual void moveOnBoard(Board& board)override;
};

#endif
