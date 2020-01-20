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
	std::cout << "2. PR2. Simulated Annealing (20 for no parameters)" << std::endl;
	std::cout << "3. PR3. Genetic algorithm (30 for default parameters)" << std::endl;
	std::cout << "4. File management" << std::endl;
	std::cout << "5. Exit";
}

void Menu::bfDispl()
{
	
	start = getTime();
	currentMatrix.bruteForce();
	end = getTime();
	std::cout << "Time: " << 1000 * (end.QuadPart - start.QuadPart) / (double)frequency.QuadPart << "ms" << std::endl;
	currentMatrix.printShortestPath();
}

void Menu::pr1Displ()
{
	bnbsolv = new bnbSolver(currentMatrix);
	start = getTime();
	bnbsolv->solve();
	end = getTime();
	std::cout << "Time: " << 1000 * (end.QuadPart - start.QuadPart) / (double)frequency.QuadPart << "ms" << std::endl;
	bnbsolv->printShortestPath();
	delete bnbsolv;

}

void Menu::pr2Displ()
{
	double temperature, absoluteTemperature, coolingRate;
	int iterations, restarts;
	std::cout << "Prosze podac: temperature, temperature koncowa, mnoznik obnizania temperatury, liczbe iteracji na poziom temperatury, liczbe restartow\n";
	std::cin >> temperature >> absoluteTemperature >> coolingRate >> iterations >> restarts;
	simulatedAnnealing = new SimulatedAnnealing(currentMatrix, temperature, coolingRate, absoluteTemperature, iterations, restarts);
	start = getTime();
	simulatedAnnealing->run();
	end = getTime();
	std::cout << "Time: " << 1000 * (end.QuadPart - start.QuadPart) / (double)frequency.QuadPart << "ms" << std::endl;
	simulatedAnnealing->printSolution();
	delete simulatedAnnealing;
}

void Menu::pr2DisplDefault()
{
	simulatedAnnealing = new SimulatedAnnealing(currentMatrix);
	start = getTime();
	simulatedAnnealing->run();
	end = getTime();
	std::cout << "Time: " << 1000 * (end.QuadPart - start.QuadPart) / (double)frequency.QuadPart << "ms" << std::endl;
	simulatedAnnealing->printSolution();
	delete simulatedAnnealing;
}

void Menu::pr3Displ()
{
	std::cout << "Prosze podac: rozmiar populacji, typ mutacji(0 inwersja, 1 transpozycja), wspó³czynnik mutacji, wspó³czynnik krzy¿owania, maksymaln¹ stagnacjê, rozmiar turnieju\n";
	int population, stagnationMax, tournamentSize;
	bool mutation;
	double mutationRate, matingRatio;
	std::cin >> population >> mutation >> mutationRate >> matingRatio >> stagnationMax >> tournamentSize;
	geneticAlgorithm = new GeneticAlgorithm(currentMatrix, population, mutation, mutationRate, matingRatio, stagnationMax, tournamentSize);
	start = getTime();
	geneticAlgorithm->run();
	end = getTime();
	std::cout << "Time: " << 1000 * (end.QuadPart - start.QuadPart) / (double)frequency.QuadPart << "ms" << std::endl;
	delete geneticAlgorithm;
}

// for quick testing
void Menu::pr3DisplDefault()
{
	geneticAlgorithm = new GeneticAlgorithm(currentMatrix, 300, false, 0.1, 0.50, 50, 50);
	start = getTime();
	geneticAlgorithm->run();
	end = getTime();
	std::cout << "Time: " << 1000 * (end.QuadPart - start.QuadPart) / (double)frequency.QuadPart << "ms" << std::endl;
	delete geneticAlgorithm;
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
			//fileName.append(".atsp");
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
		default:
			break;
		}
	}

}

void Menu::test()
{
	std::ofstream save("results.txt");
	double saveTimeSA;
	
	for (int i = 800; i <= 1000; i = i + 200)
	{
		saveTimeSA = 0;
		std::cout << i << " \n";

		for (int j = 0; j <= 100; j++)
		{
			std::cout << j;
			simulatedAnnealing = new SimulatedAnnealing(currentMatrix);
			currentMatrix.generateRandom(i);
			start = getTime();
			simulatedAnnealing->run();
			end = getTime();
			saveTimeSA += 1000 * (end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
			delete simulatedAnnealing;
		}
		save << "Dimension: " << i << "Time for Simulated Annealing: " << saveTimeSA / 100.0 << "ms\n";
	}
	save.close();
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
		case 20:
			pr2DisplDefault();
			break;
		case 30:
			pr3DisplDefault();
		case 113:
			test();
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
