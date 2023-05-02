#ifndef _MENU
#define _MENU

#include "file.h"

class Menu
{
private:
	int board_color;
	File file;
	vector<string> file_name_list;

public:
	Menu();

	int printMenu()const;

	void setBoardColor();
	void askForFile();
	void chooseLevel(int& level);

	void printInstructions()const;
	void printWinLoseMessages(int life, int file_counter)const;
	void printByeMessage()const;

	vector<string> getFileNameList();
	int getBoardColor();
	void printNoFiles();
};
#endif
