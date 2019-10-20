#include "pch.h"
#include "Menu.h"


Menu::Menu()
{
	choice = -1;
	running = true;
}


Menu::~Menu()
{
}

void Menu::setRunning()
{
}

void Menu::displayMain()
{
	std::cout << "Travelling salesman problem" << std::endl;
	std::cout << "0. Brute-force search" << std::endl;
	std::cout << "1. PR1. " << std::endl;
	std::cout << "2. PR2. " << std::endl;
	std::cout << "3. PR3. Genetic algorithm" << std::endl;
	std::cout << "4. Exit";
}

void Menu::display0()
{

}

void Menu::chooseMenu()
{
	switch (choice) {
	case 0:
		display0;
		break;
	case 4:
		running = false;
		break;
	default:
		displayMain();
	}
}
