#include "pch.h"
#include "Menu.h"


Menu::Menu()
{
	choice = -1;
	running = false;
	QueryPerformanceFrequency(&frequency);
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
	std::cout << "1. PR1. Branch and Bound" << std::endl;
	std::cout << "2. PR2. NN" << std::endl;
	std::cout << "3. PR3. Genetic algorithm" << std::endl;
	std::cout << "4. File management" << std::endl;
	std::cout << "5. Exit";
}

void Menu::bfDispl()
{
	
	start = getTime();
	currentMatrix.bruteForce();
	end = getTime();
	std::cout << "Time: " << 1000 * (end.QuadPart - start.QuadPart) / (double)frequency.QuadPart << std::endl;
	currentMatrix.printShortestPath();
}

void Menu::pr1Displ()
{
	bnbsolv = new bnbSolver(currentMatrix);
	start = getTime();
	bnbsolv->solve();
	end = getTime();
	std::cout << "Time: " << 1000 * (end.QuadPart - start.QuadPart) / (double)frequency.QuadPart << std::endl;
	bnbsolv->printShortestPath();
	delete bnbsolv;

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
		std::string fileName;
		switch (choice) {
		case 1:
			std::cout << "Enter the name of the file stored in /data/ folder(without extension): ";
			std::cin >> fileName;
			fileName.insert(0, "data/");
			fileName.append(".atsp");
			if(currentMatrix.loadFile(fileName))
				std::cout << "Loaded file: " << currentMatrix.getName() << std::endl << "Dimension: " << currentMatrix.getDimension() << std::endl;
			else
				std::cout << "Failed to load the file\n";
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

LARGE_INTEGER Menu::getTime()
{
	LARGE_INTEGER time;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&time);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return time;
}
