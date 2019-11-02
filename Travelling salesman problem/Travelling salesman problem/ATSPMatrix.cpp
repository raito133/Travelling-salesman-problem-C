#include "pch.h"
#include "ATSPMatrix.h"


int ATSPMatrix::calculatePath(std::vector<int> nodes)
{
	int distance = 0;
	distance = atspMatrix[startingNode][nodes[0]];
	for (int i = 0; i < nodes.size(); i++)
	{
		if (i + 1 != nodes.size())
			distance += atspMatrix[nodes[i]][nodes[i + 1]];
		else
			distance += atspMatrix[nodes[i]][startingNode];
	}
	return distance;
}

void ATSPMatrix::printMatrix()
{
	if (dimension == 0)
		std::cout << "No file is loaded\n";
	std::cout << "Name: " << name << ", dimension: " << dimension << std::endl;
	std::cout << std::setw(2) << "X ";
	for (int i = 0; i < atspMatrix.size(); i++)
		std::cout << std::setw(2) <<  i << " ";
	std::cout << std::endl;
	for (int i = 0; i < atspMatrix.size(); i++)
	{
		std::cout << std::setw(2) <<  i << " ";
		for (int j = 0; j < atspMatrix[i].size(); j++)
		{
			std::cout << std::setw(2);
			std::cout << atspMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool ATSPMatrix::loadFile(std::string fileName)
{
	std::ifstream load;
	load.open(fileName);
	if (!load.is_open())
	{
		return false;
	}
	atspMatrix.clear();
	std::string line;
	int number;
	while (line != "EDGE_WEIGHT_SECTION") {
		load >> line;
		if (line == "NAME:")
			load >> name;
		if (line == "DIMENSION:")
			load >> dimension;
	}

	for (int i = 0; i < dimension; i++) {
		std::vector<int> row;
		if (i != 0)
			nodes.push_back(i);
		for (int j = 0; j < dimension; j++) {
			load >> number;
			if (number == 9999)
				number = -1;
			row.push_back(number);
		}
		atspMatrix.push_back(row);
	}

	load.close();
	return true;

}

void ATSPMatrix::bruteForce()
{
	int shortestPathLength = -1, currentPath;
	std::vector<int> shortestPathNodes;
	do
	{
		currentPath = 0;
		for (int i = 0; i < nodes.size(); i++)
		{
			currentPath = calculatePath(nodes);
			if (shortestPathLength == -1 || currentPath < shortestPathLength)
			{
				shortestPathNodes = nodes;
				shortestPathLength = currentPath;
			}
		}

	} while (std::next_permutation(nodes.begin(), nodes.end()));
	std::cout << "Shortest path length: " << shortestPathLength;
	std::cout << "\nNodes: ";
	for (const int x : shortestPathNodes)
		std::cout << x << " ";
	std::cout << std::endl;
}

std::string ATSPMatrix::getName()
{
	return name;
}

int ATSPMatrix::getDimension()
{
	return dimension;
}

ATSPMatrix::ATSPMatrix()
{
	dimension = 0;
	startingNode = 0;
}


ATSPMatrix::~ATSPMatrix()
{
}
