#include "pch.h"
#include "GeneticAlgorithm.h"

struct {
	bool operator()(Individual a, Individual b) const
	{
		return a.getFitness() > b.getFitness();
	}
} customGreater;

int GeneticAlgorithm::calculatePath(std::vector<int> vertices)
{
	//take nodes and add edges for them
	//adds node 0 at start and end of the path
	int distance = 0;
	distance = matrix[0][vertices[0]];
	for (int i = 0; i < (int)vertices.size(); i++)
	{
		if (i + 1 != vertices.size())
		{
			distance += matrix[vertices[i]][vertices[i + 1]];
		}
		else
			distance += matrix[vertices[i]][0];
	}
	return distance;
}

void GeneticAlgorithm::run()
{
	int generation = 0;
	std::vector<Individual> population;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distributionInt(0, matrix.size() - 2);
	int lastFitness, stagnation = 0;
	std::uniform_int_distribution<int> distributionInt2(0, matingPoolSize-1);
	std::uniform_real_distribution<double> distributionReal(0.0, 1.0);
	/*std::vector<int> vector1 = { 1,2,3,4,5,6,7,8,9 };
	std::vector<int> vector2 = { 9,3,7,8,2,6,5,1,4 };
	Individual individual1(vector1);
	Individual individual2(vector2);
	individual1.mate(individual2);*/


	std::vector<int> chromosome;
	for (int i = 1; i < matrix.size(); i++)
	{
		chromosome.push_back(i);
	}
	// create initial population
	for (int i = 0; i < populationSize; i++)
	{
		shuffle(chromosome.begin(), chromosome.end(), generator);
		Individual newIndividual(chromosome);
		newIndividual.setFitness((-1) * calculatePath(newIndividual.getChromosome()));
		population.push_back(newIndividual);
	}
	lastFitness = population[0].getFitness();
	while (true)
	{
		std::sort(population.begin(), population.end(), customGreater);
		if (lastFitness == population[0].getFitness())
			stagnation++;
		if (lastFitness != population[0].getFitness())
		{
			lastFitness = population[0].getFitness();
			stagnation = 0;
		}
		if (stagnation == stagnationMax)
		{
			vertices = population[0].getChromosome();
			solution = calculatePath(population[0].getChromosome());
			break;
		}/*
		std::cout << "CALA POPULACJA: ";
		for (int i = 0; i < populationSize; i++)
		{
			for (const int a : population[i].getChromosome())
				std::cout << a << " ";
			std::cout << std::endl;
			std::cout << "Fitness: " << "\n";
			std::cout << population[i].getFitness() << " ";
			std::cout << std::endl;
		}
		std::cout << "KONIEC CALEJ POPULACJI";
		*/
		std::vector<Individual> newPopulation;
		std::vector<Individual> matingPool;
		std::vector<Individual> tournamentPool;

		// Elitism - the best from the population go to the next
		for (int i = 0; i < elitismPoolSize; i++)
		{
			newPopulation.push_back(population[i]);
		}

		// TOURNAMENT SELECTION
		for (int i = 0; i < matingPoolSize; i++)
		{
			std::uniform_int_distribution<int> distributionInt3(0, population.size()-1);
			int randomNumber = distributionInt3(generator);
			if (randomNumber == 0)
			{
				i = i - 1;
				continue;
			}
			int tournamentSize = 3;
			for (int a = 0; a < tournamentSize; a++)
			{
				randomNumber = distributionInt3(generator);
				tournamentPool.push_back(population[randomNumber]);
			}
			int bestFitnessTournament = tournamentPool[0].getFitness();
			Individual bestIndividual(chromosome);
			bestIndividual = tournamentPool[0];
			int bestIndividualIndex = 0;
			for (int a = 0; a < tournamentSize; a++)
			{
				if (tournamentPool[a].getFitness() > bestFitnessTournament)
				{
					bestFitnessTournament = tournamentPool[a].getFitness();
					bestIndividual = tournamentPool[a];
				}
			}
			matingPool.push_back(bestIndividual);
			tournamentPool.clear();
			
		}

		for (int i = 0; newPopulation.size() != populationSize; i++)
		{
			int randomNumber = distributionInt2(generator);
			Individual parent1 = matingPool[randomNumber];
			randomNumber = distributionInt2(generator);
			Individual parent2 = matingPool[randomNumber];
			Individual offspring = parent1.mateOrderCrossover(parent2);
			Individual offspringSecond = parent2.mateOrderCrossover(parent1);
			offspring.setFitness((-1) * calculatePath(offspring.getChromosome()));
			offspringSecond.setFitness((-1) * calculatePath(offspringSecond.getChromosome()));
			double mutationChance = distributionReal(generator);
			
			// random chance of mutation, the type of mutation depends on input
			if (mutationChance < mutationRate)
			{
				if (mutateTransposition == true)
				{
					offspring.mutateTransposition();
					offspringSecond.mutateTransposition();
				}
				else
				{
					offspring.mutateInversion();
					offspringSecond.mutateInversion();
				}

			}
			newPopulation.push_back(offspring);
			newPopulation.push_back(offspringSecond);
		}
		population = newPopulation;
		newPopulation.clear();
		std::cout << "Generation: " << generation<<"LastFitest: " << lastFitness << "\n";
		generation++;
	}

	std::cout << "Vertices: ";
	std::cout << "0->";
	for (const int x : vertices)
		std::cout << x << "->";
	std::cout << "0" << "\n";
	std::cout << "Distance: " << solution;


}

GeneticAlgorithm::GeneticAlgorithm(ATSPMatrix newAtspMatrix, int populationSize, bool mutateTransposition, double mutationRate, double matingRatio, int stagnationMax, int tournamentSize)
{
	matrix = newAtspMatrix.getMatrix();
	this->populationSize = populationSize;
	matingPoolSize = matingRatio * populationSize;
	this->stagnationMax = stagnationMax;
	this->mutateTransposition = mutateTransposition;
	this->mutationRate = mutationRate;
	this->matingRatio = matingRatio;
	this->elitismRate = 0.10;
	elitismPoolSize = elitismRate * populationSize;
	this->tournamentSize = tournamentSize;
}


GeneticAlgorithm::~GeneticAlgorithm()
{
}
