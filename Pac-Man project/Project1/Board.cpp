#include "Board.h"

#define NOT_DEFINE -1

Board::Board()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			board[i][j] = SPACE;       //init board
			pac_loc[i][j] = false;     //init pac_loc
			fruit_loc[i][j] = true;    //init pac_loc
		}
	}
	
	color = NOT_DEFINE;
	bar_col = bar_row = NOT_DEFINE;
	board_rows = board_cols = NOT_DEFINE;
};

Location Board::getPackmanLoction() { return packmanLoc; }
void Board::setPackmanLoction(Location _loc) { packmanLoc = _loc; }

// board
void Board::startNewBoard()
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			board[i][j] = SPACE;
}
char Board::whatInBoard(int row, int col)const { return board[row][col]; }
void Board::setBoardCell(int row, int col, char mark)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	board[row][col] = mark;

	if (color == WITH_COLOR)
	{
		if (mark == PACKMAN)
			SetConsoleTextAttribute(hConsole, YELLOW);
		else if (mark == GHOST)
			SetConsoleTextAttribute(hConsole, LIGHTRED);
		else
			SetConsoleTextAttribute(hConsole, WHITE);
	}
	gotoxy(col, row);
	cout << mark;
	SetConsoleTextAttribute(hConsole, WHITE);

}
void Board::printBoard()const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (color == WITH_COLOR)
			{
				if (board[i][j] == BOARD)
					SetConsoleTextAttribute(hConsole, LIGHTCYAN);
				else if (board[i][j] == PACKMAN)
					SetConsoleTextAttribute(hConsole, YELLOW);
				else if (board[i][j] == GHOST)
					SetConsoleTextAttribute(hConsole, LIGHTRED);
				else
					SetConsoleTextAttribute(hConsole, WHITE);

				cout << board[i][j];

				SetConsoleTextAttribute(hConsole, WHITE);
			}
			else //  WITHOUT_COLOR
				cout << board[i][j];
		}
		cout << endl;
	}
}

// pac loc
char Board::whatInPacLoc(int row, int col)const
{
	if (pac_loc[row][col]) // packman was in this location and eaten the bread crumb that was there
		return SPACE;
	return BREAD_CRUMBS; // packman wasn't in this location and the bread crumb in it is still there
}
void Board::setPacLocCell(int row, int col)
{
	if (!pac_loc[row][col]) // packman wasn't in this location yet
		pac_loc[row][col] = true;
}
bool Board::checkPacLocCell(int row, int col)
{
	if (!pac_loc[row][col]) // packman wasn't in this location yet
		return true;
	return false;
}
void Board::initPacLoc()
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			pac_loc[i][j] = false;
}

// fruit location
void Board::initFruitLoc()
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			fruit_loc[i][j] = false;
}
void Board::setFruitLocCell(int row, int col)
{
	fruit_loc[row][col] = true;
}
bool Board::checkFruitLocCell(int row, int col)
{
	if (fruit_loc[row][col])
		return true;
	return false;
}

// bar
void Board::updateBarLoc(int row, int col) { bar_row = row; bar_col = col; }
void Board::printBar(int life, int points)
{
	gotoxy(bar_col, bar_row);

	if (color == WITH_COLOR)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, WHITE);
		cout << "life: ";

		SetConsoleTextAttribute(hConsole, RED);
		for (int i = 0; i < life; i++)
			cout << char(3) << SPACE;
		cout << endl;

		gotoxy(bar_col, bar_row + 1);

		SetConsoleTextAttribute(hConsole, WHITE);
		cout << "points: ";

		SetConsoleTextAttribute(hConsole, LIGHTGREEN);
		cout << points << endl;

		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else if (color == WITHOUT_COLOR)
	{
		cout << "life: ";

		for (int i = 0; i < life; i++)
			cout << char(3) << " ";

		gotoxy(bar_col, bar_row + 1);

		cout << endl << "points: " << points << endl;
	}
	
}

void Board::setColor(int _color) { color = _color; }
void Board::initSpot(int row, int col, char mark) { board[row][col] = mark; }

void Board::getBoard(string file_name, int& rows_num, int& cols_num)
{
	int counter = 0;
	char line[COL + 1] = { 0 };
	bool found_first_line = false;

	ifstream myfile(file_name, ios::in);

	if (myfile.fail()) 
		cout << "file failed!!";
	
	// get first row
	if (!myfile.eof()) { myfile.getline(line, COL + 1); }
	else { cout << "Empty file!" << endl; }

	cols_num = (int)strlen(line); // find board cols number

	do {
		
		for (int col = 0; col < (int)strlen(line); col++)
			board[counter][col] = line[col];
		counter++;
		
		myfile.getline(line, COL + 1);

	} while (!myfile.eof());

	for (int col = 0; col < (int)strlen(line); col++)
		board[counter][col] = line[col];
	counter++;

	myfile.close();
	rows_num = counter;
}

void Board::getBoardSize(int& row_size, int& col_size)
{
	row_size = board_rows;
	col_size = board_cols;
}
void Board::setBoardSize(int row_size, int col_size)
{
	board_rows = row_size;
	board_cols = col_size;
}

vector<vector<Location>> Board::getTunnels()
{
	return tunnels;
}
void Board::setTunnels(vector<vector<Location>> _tunnels)
{
	tunnels = _tunnels;
}
