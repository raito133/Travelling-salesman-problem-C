#include "pch.h"
#include "SimulatedAnnealing.h"


double SimulatedAnnealing::changeTemperature(double temperature)
{
	return temperature * coolingRate;
}

int SimulatedAnnealing::calculatePath(std::vector<int> vertices)
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

std::vector<int> SimulatedAnnealing::getNextSolution(std::vector<int> currentSolution)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distributionInt(0, matrix.size()-2);
	int i = 0, j = 0;
	while (i == j)
	{
		i = distributionInt(generator);
		j = distributionInt(generator);
	}
	int temp = currentSolution[i];
	currentSolution[i] = currentSolution[j];
	currentSolution[j] = temp;
	
	return currentSolution;
}

std::vector<int> SimulatedAnnealing::getStartingSolution()
{
	std::vector<int> solution;
	for (int i = 1; i < matrix.size(); i++)
	{
		solution.push_back(i);
	}
	return solution;
}

std::vector<int> SimulatedAnnealing::anneal()
{
	// random number generator (double)
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	std::vector<int> currentSolution = getStartingSolution();
	bestSolution = currentSolution;
	std::vector<int> nearbySolution;

	// iterations determine how many solutions do we want to check for a given temperature level
	currentSolution = getStartingSolution();

	while (temperature > absoluteTemperature)
	{
		for (int i = 0; i < iterations; i++)
		{
			nearbySolution = getNextSolution(currentSolution);

			// remember the best solution so far
			if (calculatePath(nearbySolution) < calculatePath(bestSolution))
				bestSolution = nearbySolution;

			deltaDistance = calculatePath(nearbySolution) - calculatePath(currentSolution);

			// if the current solution is better it is accepted 
			if (deltaDistance < 0)
				currentSolution = nearbySolution;

			// if not we use the temperature and random factor to determine if we should accept it
			else
			{
				if (exp(-deltaDistance / temperature) > distribution(generator))
					currentSolution = nearbySolution;

			}
		}
		temperature = changeTemperature(temperature);
	}
	return bestSolution;
}

void SimulatedAnnealing::run()
{
	bestSolution = anneal();
}

std::vector<int> SimulatedAnnealing::getSolutionVertices()
{
	return bestSolution;
}

int SimulatedAnnealing::getSolutionDistance()
{
	return calculatePath(bestSolution);
}

void SimulatedAnnealing::printSolution()
{
	std::cout << "Best vertices: ";
	std::cout << "0->";
	for (const int x : bestSolution)
		std::cout << x << "->";
	std::cout << "->0" << "\n";
	std::cout << "Distance: " << getSolutionDistance() << "\n";
}

SimulatedAnnealing::SimulatedAnnealing(ATSPMatrix newAtspMatrix)
{
	matrix = newAtspMatrix.getMatrix();
	temperature = 10000000000.0;
	absoluteTemperature = 0.0001;
	coolingRate = 0.99;
	iterations = matrix.size() * 4; // we check more similar paths the bigger the matrix
}


SimulatedAnnealing::~SimulatedAnnealing()
{
}
