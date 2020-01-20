#pragma once
#include <vector>
#include <random>
#include <iostream>
class Individual
{
	int fitness; // how fit is this individual
	std::vector<int> chromosome;
public:
	void setFitness(int fitness);
	int getFitness();
	std::vector<int> getChromosome();
	void mutateTransposition();
	void mutateInversion();
	Individual(std::vector<int> chromosome);
	Individual mateOrderCrossover(Individual secondIndividual);
	~Individual();
};

