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
	std::cout << "4. File management" << std::endl;
	std::cout << "5. Exit";
}

void Menu::bfDispl()
{

}

void Menu::pr1Displ()
{
}

void Menu::pr2Displ()
{
}

void Menu::pr3Displ()
{
}

void Menu::filDispl()
{
	bool run = true;
	while (run)
	{
		std::cout << "\n1. Load from file" << std::endl;
		std::cout << "2. Print loaded data" << std::endl;
		std::cout << "3. Go back" << std::endl;
		std::cin >> choice;
		switch (choice) {
		case 1:
			currentMatrix.loadFile("br17.atsp");
			break;
		case 2:
			currentMatrix.printMatrix();
			break;
		case 3:
			run = false;
			break;
		}
	}

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
			filDispl();
			break;
		case 5:
			running = false;
			break;
		}

	}
}
