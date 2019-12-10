#pragma once
#include "ATSPMatrix.h"
#include <cmath>
#include <random>

class SimulatedAnnealing
{
	std::vector<std::vector<int>> matrix;
	std::vector<int> bestSolution;
	double temperature;
	double coolingRate;
	double deltaDistance;
	double absoluteTemperature;
	int iterations;
	int restarts;
	double changeTemperature(double temperature);
	int calculatePath(std::vector<int> vertices);
	std::vector<int> getNextSolution(std::vector<int> currentSolution);
	std::vector<int> getStartingSolution();
	std::vector<int> anneal();
public:
	void run();
	std::vector<int> getSolutionVertices();
	int getSolutionDistance();
	void printSolution();
	SimulatedAnnealing(ATSPMatrix atspMatrix);
	~SimulatedAnnealing();
};

