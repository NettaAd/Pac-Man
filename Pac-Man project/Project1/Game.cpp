#include "Game.h"

Game::Game() 
{
	points = points_to_earn = 0;
	level = 0;
	end_game = false;
	life = 3;
}

void Game::checkWin() 
{
	if (points == points_to_earn)
		end_game = true;		
}
void Game::checkEndGame()
{
	int row, col;

	if (!end_game)
		life--;

	if (life == 0)
		end_game = true;

	if (!end_game)
	{
		// init the board
		packman.getLocation(row, col);
		theGameBoard.setBoardCell(row, col, theGameBoard.whatInPacLoc(row, col));

		for (int i = 0; i < ghosts.size(); i++)
		{
			ghosts[i].getLocation(row, col);
			theGameBoard.setBoardCell(row, col, theGameBoard.whatInPacLoc(row, col));
		}
	}
	
	// init the game objects location
	int object_row, object_col;
	packman.initLocation();
	packman.getLocation(object_row, object_col);
	
	theGameBoard.setBoardCell(object_row, object_col, PACKMAN);

	for (int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i].initLocation();
		ghosts[i].getLocation(object_row, object_col);
		theGameBoard.setBoardCell(object_row, object_col, GHOST);
	}

	system("cls");
}

void Game::start()
{
	int file_counter = 0;
	while (!end_game)
	{
		int choise = menu.printMenu();

		if (choise == NEW_GAME)
		{
			menu.askForFile();
			menu.chooseLevel(level);
			menu.setBoardColor();
			
			life = 3;
			points = points_to_earn = 0;
			file_counter = 0;

			if (menu.getFileNameList().size() == 0)
			{
				menu.printNoFiles();
				choise = EXIT;
			}
				
			while (file_counter < menu.getFileNameList().size())
			{

				init(menu.getFileNameList()[file_counter]);

				while (!end_game)
					playNewGame(menu.getBoardColor());

				file_counter++;
				end_game = false;
				menu.printWinLoseMessages(life, file_counter);

				system("cls");			

				if (life == 0)
				{
					life = 3;
					points = points_to_earn = 0;
					file_counter = 0;
					menu.getFileNameList().clear();
					break;
				}
			}
		}

		if (choise == INSTRUCTIONS)
			menu.printInstructions();

		if (choise == EXIT)
		{
			menu.printByeMessage();
			end_game = true;
		}
	}
}

void Game::playNewGame(int if_color)
{
	int move_counter = 1;
	int status = NO_CRASH;
	char ch;
	int is_fruit_alive;

	/* initialize random seed for the ghost dieraction: */
	srand(time(0));

	theGameBoard.setColor(if_color);
	theGameBoard.printBoard();
	theGameBoard.printBar(life, points);
	
	// while the palyer has not start to move packman
	beforeFirstMove(status);
	packman.setStatus(status);
	
	// the player push the kebord for the first time
	if (packman.getStatus() != STRIKE)
	{
		ch = _getch();
		if (ch == ESC)
			packman.ifESC();
	}

	is_fruit_alive = rand() % FRUIT_PROBABILITY;
	fruit.setFruitOnBoard(theGameBoard, is_fruit_alive);

	afterFirstMove(status, move_counter, ch, is_fruit_alive);
	packman.setStatus(status);
	
	// if status == STRIKE the function take down one packman live
	checkEndGame();
}
void Game::beforeFirstMove(int& status)
{
	while (!_kbhit())
	{
		Sleep(2 * SPEED);

		for (int i = 0; i < ghosts.size() && status != STRIKE; i++)
		{
			int row, col;
			packman.getLocation(row, col);
			theGameBoard.setPackmanLoction(Location(row, col));
			ghosts[i].setLevel(level);

			status = ghosts[i].move(theGameBoard);
		}

		if (status == STRIKE)
			return;

	}
}
void Game::afterFirstMove(int& status, int& move_counter, char& ch, int& is_fruit_alive)
{
	int row, col;
	int fruit_time_to_live = 0;

	while (!end_game && status != STRIKE)
	{
		Sleep(SPEED);
		srand(time(0));

		if (is_fruit_alive < FRUIT_LIVES)
		{
			if (move_counter % 3 == 1)
			{
				status = fruit.move(theGameBoard);
				theGameBoard.printBar(life, points);
				if (status == STRIKE_FRUIT_PACKMAN)
				{
					points += fruit.getValue();
					points_to_earn += fruit.getValue();
					is_fruit_alive = FRUIT_PROBABILITY; //kill fruit
					fruit.setFruitOnBoard(theGameBoard, is_fruit_alive);
				}
				else if (status == STRIKE_FRUIT_GHOST)
				{
					is_fruit_alive = FRUIT_PROBABILITY; //kill fruit
					fruit.setFruitOnBoard(theGameBoard, is_fruit_alive);
				}		
			}

			if (fruit_time_to_live % FRUIT_KILL_STEPS == 0)
				is_fruit_alive = FRUIT_PROBABILITY; //kill fruit
			
		}
		else if(fruit_time_to_live != FRUIT_KILL_FOREVER)
		{
			is_fruit_alive = rand() % FRUIT_PROBABILITY;
			fruit.setFruitOnBoard(theGameBoard, is_fruit_alive);
		}

		if (move_counter % 2 == 1) // every 2 steps of packman == 1 step of each ghost
		{
			for (int i = 0; i < ghosts.size() ; i++)
			{
				if (status == STRIKE)
					break;
				int row, col;
				packman.getLocation(row, col);
				theGameBoard.setPackmanLoction(Location(row, col));

				status = ghosts[i].move(theGameBoard);

				if (status == STRIKE_FRUIT_GHOST)
				{
					is_fruit_alive = 10; //kill fruit
					fruit.setFruitOnBoard(theGameBoard, is_fruit_alive);
				}
					
			}
			if (status == STRIKE)
				return;
		}

		fruit_time_to_live++;
		move_counter++;

		packman.setCh(ch);
		packman.setStatus(status);

		status = packman.move(theGameBoard);
		ch = packman.getCh();

		theGameBoard.printBar(life, points);

		packman.getLocation(row, col);
		bool add_point = theGameBoard.checkPacLocCell(row, col);
		if (add_point)
		{
			points++;
			checkWin();
		}
		theGameBoard.setPacLocCell(row, col);
		theGameBoard.printBar(life, points);

		if (status == STRIKE_FRUIT_PACKMAN) 
		{
			points += fruit.getValue();
			points_to_earn += fruit.getValue();
			is_fruit_alive = FRUIT_PROBABILITY; //kill fruit
			fruit.setFruitOnBoard(theGameBoard, is_fruit_alive);
		}
	}
}

void Game::makeTunnels()
{
	char what_in_board1, what_in_board2;
	int board_rows, board_cols;
	vector<vector<Location>> tunnels;
	theGameBoard.getBoardSize(board_rows, board_cols);

	for (int col = 0; col < board_cols; col++)  // up-down tunnels
	{
		what_in_board1 = theGameBoard.whatInBoard(0, col);
		what_in_board2 = theGameBoard.whatInBoard(board_rows - 1 , col);

		if (what_in_board1 == ' ' && what_in_board2 == ' ')
		{
			tunnels.push_back({ Location(0, col), Location(board_rows - 1 , col) });
			theGameBoard.initSpot(0, col, '^');
			theGameBoard.initSpot(board_rows - 1 , col, '^');
		}
		
	}

	for (int row = 0; row < board_rows; row++) // left-right tunnels
	{
		what_in_board1 = theGameBoard.whatInBoard(row, 0);
		what_in_board2 = theGameBoard.whatInBoard(row, board_cols - 1);

		if (what_in_board1 == ' ' && what_in_board2 == ' ')
		{
			tunnels.push_back({ Location(row, 0), Location(row, board_cols - 1) });
			theGameBoard.initSpot(row, 0, '^');
			theGameBoard.initSpot(row, board_cols - 1, '^');
		}

	}	
	theGameBoard.setTunnels(tunnels);
}
void Game::initBoard()
{
	int board_rows, board_cols;
	theGameBoard.getBoardSize(board_rows, board_cols);

	for (int row = 0; row < board_rows; row++)
		for (int col = 0; col < board_cols; col++)		
			if (theGameBoard.whatInBoard(row, col) == ' ') 
			{
				theGameBoard.initSpot(row, col, BREAD_CRUMBS);
				theGameBoard.setFruitLocCell(row, col);
				points_to_earn++;
			}
	

	for (int row = 0; row < board_rows; row++)
		for (int col = 0; col < board_cols; col++)
		{
			if (theGameBoard.whatInBoard(row, col) == '#')
			{
				theGameBoard.initSpot(row, col, BOARD);
				theGameBoard.setFruitLocCell(row, col);
			}

			else if (theGameBoard.whatInBoard(row, col) == ' ')
			{
				theGameBoard.initSpot(row, col, SPACE);
			}

			else if (theGameBoard.whatInBoard(row, col) == '@')
			{
				packman.setStartLocation(row, col);

				packman.setLocation(row, col);
				packman.setTmpLocation(row, col);

				theGameBoard.setPacLocCell(row, col);
				theGameBoard.initSpot(row, col, PACKMAN);
			}

			else if (theGameBoard.whatInBoard(row, col) == '$')
			{
				Ghost ghost(Location(row, col)); // create a new ghost
				ghosts.push_back(ghost);
				theGameBoard.initSpot(row, col, GHOST);
				points_to_earn++;
			}

			else if (theGameBoard.whatInBoard(row, col) == '%')
			{
				theGameBoard.initSpot(row, col, SPACE);
				theGameBoard.setPacLocCell(row, col);
			}

			else if (theGameBoard.whatInBoard(row, col) == '&')
			{
				theGameBoard.updateBarLoc(row, col);
				theGameBoard.initSpot(row, col, SPACE);
			}

			else if (theGameBoard.whatInBoard(row, col) == '^')
			{
				theGameBoard.initSpot(row, col, SPACE);
			}
		}
}
void Game::init(string file_name)
{
	int board_rows, board_cols;
	end_game = false;

	// ------------ clear all vectors --------------
	for (int i = 0; i < theGameBoard.getTunnels().size(); i++)
		theGameBoard.getTunnels()[i].clear();
	theGameBoard.getTunnels().clear();
	theGameBoard.startNewBoard();
	theGameBoard.initPacLoc();
	theGameBoard.initFruitLoc();
	fruit.setLocation(0, 0);
	fruit.setTmpLocation(0, 0);
	ghosts.clear();

	


	// ------------- get the new board fron the next file -----------
	theGameBoard.getBoard(file_name, board_rows, board_cols);
	theGameBoard.setBoardSize(board_rows, board_cols);

	makeTunnels();
	initBoard();

}