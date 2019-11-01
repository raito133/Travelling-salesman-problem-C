// Travelling salesman problem.cpp : This file contains "main"
//

#include "pch.h"
#include <iostream>
#include "Menu.h"

int main()
{
	Menu menu;
	if (menu.isRunning() == false) {
		menu.run();
	}

	return 0;
}