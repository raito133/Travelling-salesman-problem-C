#include "pch.h"
#include "Individual.h"

void Individual::setFitness(int fitness)
{
	this->fitness = fitness;
}

int Individual::getFitness()
{
	return fitness;
}

std::vector<int> Individual::getChromosome()
{
	return chromosome;;
}

void Individual::mutateTransposition()
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distributionInt(0, chromosome.size()-1);

	int i = 0, j = 0;
	while (i == j)
	{
		i = distributionInt(generator);
		j = distributionInt(generator);
	}
	int temp = chromosome[i];
	chromosome[i] = chromosome[j];
	chromosome[j] = temp;
	
}

void Individual::mutateInversion()
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distributionInt(0, chromosome.size() - 1);
	int i = 0, j = 0;
	while (i == j)
	{
		i = distributionInt(generator);
		j = distributionInt(generator);
	}
	std::vector<int> temp;
	// swapping
	if (i < j)
	{
		for (int x = j-1; x >= i; x--)
		{
			temp.push_back(chromosome[x]);
		}
		int a = 0;
		for (int x = i; x < j; x++)
		{
			
			chromosome[x] = temp[a];
			a++;
		}
	}
	else
	{
		for (int x = i-1; x >=j; x--)
		{
			temp.push_back(chromosome[x]);
		}
		int a = 0;
		for (int x = j; x < i; x++)
		{
			chromosome[x] = temp[a];
			a++;
		}
	}
}

Individual::Individual(std::vector<int> chromosome)
{
	this->chromosome = chromosome;
}

// Produces offspring using OrderCrossover
Individual Individual::mateOrderCrossover(Individual secondIndividual)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distributionInt(0, chromosome.size() - 1);
	int i = 0, j = 0;
	while (i == j)
	{
		i = distributionInt(generator);
		j = distributionInt(generator);
		// adjust i and j so there are always three parts for crossover
		if (i == 0)
		{
			i++;
		}
		if (j == chromosome.size() - 1)
			j--;
		if (i > j)
		{
			int temp = j;
			j = i;
			i = temp;
		}
	}
	std::vector<int> newChromosome;
	for (int a = 0; a < chromosome.size(); a++)
		newChromosome.push_back(-1); //initializing with numbers to get the desired size
	
	// copy a segment from the first parent to the child
	for (int a = i; a < j; a++)
	{
		newChromosome[a] = chromosome[a];
	}
	
	// copy the unused genes from parent 2 to the child, starting from after the copied segment
	//unused genes:
	int x = j;
	for (int a = j; a != i; a++)
	{
		bool used = false;
		// rotation
		if (a == chromosome.size())
			a = 0;
		if (x == chromosome.size())
			x = 0;
		// check if used
		for (int c = i; c < j; c++)
		{
			if (newChromosome[c] == secondIndividual.getChromosome()[x])
				used = true;
		}
		if (used == true)
		{
			a--;
		}
		else
		{
			newChromosome[a] = secondIndividual.getChromosome()[x];
		}
		
		x++;
	}
	return Individual(newChromosome);
}


Individual::~Individual()
{
}
