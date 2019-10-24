#pragma once
#include <iostream>
class Menu
{
	int choice;
	bool running;
	void displayMain();
	void bfDispl();
	void pr1Displ();
	void pr2Displ();
	void pr3Displ();
	
public:
	Menu();
	~Menu();
	
	bool isRunning();
	void run();

};

