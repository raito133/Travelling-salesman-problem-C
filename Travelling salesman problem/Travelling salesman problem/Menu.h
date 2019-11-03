#pragma once
#include <iostream>
#include "ATSPMatrix.h"
#include "bnbSolver.h"
class Menu
{
	int choice;
	bool running;
	void displayMain();
	void bfDispl();
	void pr1Displ();
	void pr2Displ();
	void pr3Displ();
	void filDispl();
	ATSPMatrix currentMatrix;
	bnbSolver* bnbsolv;

	
public:
	Menu();
	~Menu();
	
	bool isRunning();
	void run();

};

