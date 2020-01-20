#pragma once

#include "Individual.h"
#include <vector>
#include "ATSPMatrix.h"
#include <random>
class GeneticAlgorithm
{
	std::vector<std::vector<int>> matrix;
	std::vector<int> bestSolution;
	int calculatePath(std::vector<int> vertices);
	int populationSize;
	double matingRatio;
	int matingPoolSize;
	int stagnationMax;
	double mutationRate;
	double elitismRate;
	int elitismPoolSize;
	bool mutateTransposition;
	int solution;
	std::vector<int> vertices;
	int tournamentSize;
public:
	void run();
	GeneticAlgorithm(ATSPMatrix newAtspMatrix, int populationSize, bool mutateTransposition, double mutationRate, double matingRatio, int stagnationMax, int tournamentSize);
	~GeneticAlgorithm();
};

