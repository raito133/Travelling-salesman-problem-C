#pragma once
#include <iostream>
class Menu
{
	int choice;
	bool running;
	void displayMain();
	void display0();
	void chooseMenu();
public:
	Menu();
	~Menu();
	
	void setRunning();

};

