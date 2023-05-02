#include "Ghost.h"

Ghost::Ghost(Location _loc)
{
	int row, col;
	start = _loc;
	level = 0;
	steps_counter_race = 0;
	steps_counter_rand = 0;
	_loc.getRowCol(row, col);
	setLocation(row, col); 
	setTmpLocation(row, col);
}

void Ghost::setLevel(int _level) { level = _level; }
float Ghost::distance(int x1, int y1, int x2, int y2) { return (float)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0); }
void Ghost::initLocation()
{
	int row, col;
	start.getRowCol(row, col); 
	setLocation(row, col);
	setTmpLocation(row, col);
}
bool Ghost::isInTunnel(vector<vector<Location>> tunnels, Location loc)
{
	for (int i = 0; i < tunnels.size(); i++)
		for (int j = 0; j < 2; j++)
			if (compLoc(loc, tunnels[i][j]))
				return true;

	return false;
}
vector<float> Ghost::findMinimumDistance(float x1, float x2, float x3, float x4)
{
	vector<float> min = { x1,x2,x3,x4 };

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (min[i] < min[j])
			{
				float tmp = min[i];
				min[i] = min[j];
				min[j] = tmp;
			}

	return min;
}
vector<int> Ghost::findPackmanDirecion(int packman_row, int packman_col)
{
	float left_distance, right_distance, up_distance, down_distance;
	int cur_row, cur_col;
	vector<int> dirArr;
	vector<float> minimumDistance;
	getLocation(cur_row, cur_col);

	left_distance = distance(cur_row, cur_col - 1, packman_row, packman_col);
	right_distance = distance(cur_row, cur_col + 1, packman_row, packman_col);
	up_distance = distance(cur_row - 1, cur_col, packman_row, packman_col);
	down_distance = distance(cur_row + 1, cur_col, packman_row, packman_col);

	minimumDistance = findMinimumDistance(left_distance, right_distance, up_distance, down_distance);

	for (int i = 0; i < 4; i++)
	{
		if (minimumDistance[i] == left_distance)
			dirArr.push_back(LEFT);

		else if (minimumDistance[i] == right_distance)
			dirArr.push_back(RIGHT);

		else if (minimumDistance[i] == up_distance)
			dirArr.push_back(UP);

		else if (minimumDistance[i] == down_distance)
			dirArr.push_back(DOWN);
	}
	return dirArr;
}

void Ghost::setRaceStepsCounter(int _counter) { steps_counter_race = _counter; }
int Ghost::getRaceStepsCounter() { return steps_counter_race; }

void Ghost::setRandStepsCounter(int _counter) { steps_counter_rand = _counter; }
int Ghost::getRandStepsCounter() { return steps_counter_rand; }

int Ghost::move(Board& board)
{
	int stepStatus = CRASH_BOARDER;
	int cur_row, cur_col, prev_row = -1, prev_col = -1;

	bool raceMode = true;
	vector<int> dirArr;

	if (level == BEST)
	{
		int i = -1; // so the first index will be 0

		Location packmanLoc = board.getPackmanLoction();
		packmanLoc.getRowCol(cur_row, cur_col);

		if (cur_row != prev_row || cur_col != prev_col) // pacman moved >> make new dirArr, else, use the same dirArr from prev step
		{
			dirArr = findPackmanDirecion(cur_row, cur_col);
			cur_row = prev_row;  cur_col = prev_col;
		}
		while (stepStatus == CRASH_BOARDER || stepStatus == TUNNEL) // if the ghost hit border or tunnel it needs to change direction
		{
			if (i < 4)
				i++;
			changeLocation(dirArr[i]);
			stepStatus = checkMove(board);
		}
	}

	else if (level == GOOD)
	{
		int steps_counter_race = getRaceStepsCounter(), steps_counter_rand = getRandStepsCounter();
		if (steps_counter_race == 20)
		{
			raceMode = false;
			if (steps_counter_rand == 5)
			{
				raceMode = true;
				steps_counter_race = 0;
				steps_counter_rand = 0;
				setRaceStepsCounter(steps_counter_race);
				setRandStepsCounter(steps_counter_rand);
			}
		}

		if (raceMode)
		{
			int i = -1;
			Location packmanLoc = board.getPackmanLoction();
			packmanLoc.getRowCol(cur_row, cur_col);
			if (cur_row != prev_row || cur_col != prev_col) // pacman moved >> make new dirArr, else, use the same dirArr from prev step
			{
				dirArr = findPackmanDirecion(cur_row, cur_col);
				cur_row = prev_row;  cur_col = prev_col;
			}
			while (stepStatus == CRASH_BOARDER || stepStatus == TUNNEL) // if the ghost hit border or tunnel it needs to change direction
			{
				if (i < 4)
					i++;
				changeLocation(dirArr[i]);
				stepStatus = checkMove(board);
			}
			steps_counter_race++;
			setRaceStepsCounter(steps_counter_race);
		}
		else
		{
			while (stepStatus == CRASH_BOARDER || stepStatus == TUNNEL) // if the ghost hit border or tunnel it needs to change direction
			{
				changeLocation(rand() % 4);
				stepStatus = checkMove(board);
			}

			steps_counter_rand++;
			setRandStepsCounter(steps_counter_rand);
		}
	}

	else if (level == NOVICE)
	{
		while (stepStatus == CRASH_BOARDER || stepStatus == TUNNEL) // if the ghost hit border or tunnel it needs to change direction
		{
			changeLocation(rand() % 4);
			stepStatus = checkMove(board);

		}
	}
	moveOnBoard(board);
	return stepStatus;
}
int Ghost::checkMove(Board& board)
{
	int tmp_row, tmp_col, row, col;
	int status = NO_CRASH;
	int board_rows, board_cols;

	board.getBoardSize(board_rows, board_cols);

	getLocation(row, col);
	getTmpLocation(tmp_row, tmp_col);

	char what_in_board = board.whatInBoard(tmp_row, tmp_col);

	if (isInTunnel(board.getTunnels(), Location(tmp_row, tmp_col))) 
		status = TUNNEL;   // need to change direction
	
	else if (what_in_board == BOARD) 
		status = CRASH_BOARDER;

	else if (!insideBoard(board_rows, board_cols, tmp_row, tmp_col))
		status = CRASH_BOARDER;

	else if (what_in_board == PACKMAN) 	
		status = STRIKE;

	else if (what_in_board >= '5' && what_in_board <= '9')
		status = STRIKE_FRUIT_GHOST;

	if (status != NO_CRASH)
		setTmpLocation(row, col);

	return status;
}
void Ghost::moveOnBoard(Board& board)
{
	int tmp_row, tmp_col, row, col;
	getLocation(row, col);
	getTmpLocation(tmp_row, tmp_col);

	// mark where packman was on the board 
	board.setBoardCell(row, col, board.whatInPacLoc(row, col));

	row = tmp_row; 	// update row and col in new location
	col = tmp_col;
	setLocation(row, col);
	setTmpLocation(row, col);

	// update board for object move
	board.setBoardCell(row, col, GHOST);
}
