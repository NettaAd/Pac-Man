#include "menu.h"

enum { SELECT_FILE = 1, LEXICOGRAPHIC = 2 };

Menu::Menu() : board_color(WITHOUT_COLOR) {}

int Menu::printMenu()const
{
	int choosen;
	cout << endl << "	Hello! Please choose:" << endl << "	(1) Start a new game" << endl << "	(8) Present instructions and keys" << endl << "	(9) EXIT" << endl;
	cin >> choosen;
	system("cls");
	return choosen;
}

void Menu::askForFile()
{
	int if_file;
	string file_name;

	cout << endl << "	How would you like to play?" << endl;
	cout << "	(1) Select a file         (2) Lexicographic files" << endl;
	cin >> if_file;

	file_name_list.clear();

	if (if_file == SELECT_FILE)
	{
		
		cout << "Please enter the file name: ";
		cin >> file_name;
		file_name_list = file.findFile(file_name);
	}

	else if(if_file == LEXICOGRAPHIC)
		file_name_list = file.createFileList();
	
	system("cls");
}
void Menu::chooseLevel(int& level)
{
	cout << endl << "	At what level would you like to play?" << endl;
	cout << "	(1) BEST        (2) GOOD          (3) NOVICE " << endl;
	cin >> level;
	system("cls");
}
void Menu::setBoardColor() 
{
	cout << endl << "	Last question, promise!" << endl << "	Would you like a black and white or colored game board ? " << endl;
	cout << "	(1) Black & White         (2) Colourful" << endl;
	cin >> board_color;
	system("cls");
}

void Menu::printInstructions()const
{
	cout << "Instructions Pacman" << endl << endl
		<< "Goal:" << endl
		<< "Guide Pacman around the maze and eat all the little white dots whilst avoiding those nasty ghosts." << endl
		<< "If you eat a Power Pill, you can eat the ghosts!Occasionally, a fruit appears which gives you a bonus score when eaten." << endl << endl
		<< "Controls:" << endl 
		<< "Arrow keys for Pacman:" << endl
		<< "ESC : pause / unpause game" << endl
		<< "w / W : go up" << endl
		<< "d / D : go right" << endl
		<< "x / X : go down" << endl
		<< "a / A : go left" << endl
		<< "s / S : stay" << endl << endl;

	cout << "To return to the menu, press any key :)" << endl;
	char ch = _getch();
	system("cls");
}
void Menu::printWinLoseMessages(int life, int file_counter)const
{
	gotoxy(10, 5);
	if (life == 0) // lose
	{
		cout << "YOU LOSE! :(" << endl;
		cout << endl << endl << endl << "To return to the menu, press any key :)";
	}
	else // win
	{
		cout << "YOU WIN! :)" << endl;
		if (file_counter == file_name_list.size())
			cout << endl << endl << endl << "To return to the menu, press any key :)";
		else
			cout << endl << endl << endl << "To move to next screen, press any key :)";
	}
	
	char ch = _getch();

	system("cls");
}
void Menu::printByeMessage()const
{
	gotoxy(10, 5);
	cout << "BYE! :)" << endl;
}

vector<string> Menu::getFileNameList() { return file_name_list; }
int Menu::getBoardColor() { return board_color; }
void Menu::printNoFiles()
{
	system("cls");
	cout << "No files were found!" << endl;
}