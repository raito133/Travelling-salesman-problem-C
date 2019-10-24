#include "pch.h"
#include "Menu.h"


Menu::Menu()
{
	choice = -1;
	running = false;
}


Menu::~Menu()
{
}

bool Menu::isRunning()
{
	return running;
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

void Menu::bfDispl()
{

}


void Menu::run()
{
	running = true;
	while (running)
	{
		displayMain();
		std::cin >> choice;
		switch (choice) {
		case 0:
			bfDispl();
			break;
		case 1:
			pr1Displ();
			break;
		case 2:
			pr2Displ();
			break;
		case 3:
			pr3Displ();
			break;
		case 4:
			running = false;
			break;
		}

	}
}
