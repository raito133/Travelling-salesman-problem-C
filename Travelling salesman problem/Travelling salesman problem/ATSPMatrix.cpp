#include "pch.h"
#include "ATSPMatrix.h"


int ATSPMatrix::calculatePath(std::vector<int> nodes)
{
	//take nodes and add edges for them
	//adds node 0 at start and end of the path
	int distance = 0;
	distance = atspMatrix[startingNode][nodes[0]];
	for (int i = 0; i < (int)nodes.size(); i++)
	{
		if (i + 1 != nodes.size())
		{
			distance += atspMatrix[nodes[i]][nodes[i + 1]];
		}
		else
			distance += atspMatrix[nodes[i]][startingNode];
	}
	return distance;
}

int ATSPMatrix::calculatePartialPath(std::vector<int> nodes)
{
	int distance = 0;
	for (int i = 0; i < (int)nodes.size()-1; i++)
	{
		distance += atspMatrix[nodes[i]][nodes[i + 1]];
	}
	return distance;
}

void ATSPMatrix::printMatrix()
{
	if (dimension == 0)
	{
		std::cout << "No file is loaded\n";
		return;
	}
	std::cout << "Name: " << name << ", dimension: " << dimension << std::endl;
	for (int i = -1; i < (int)atspMatrix.size(); i++)
		std::cout << std::setw(4) <<  i << " ";
	std::cout << std::endl;
	for (int i = 0; i < (int)atspMatrix.size(); i++)
	{
		std::cout << std::setw(4) <<  i << " ";
		for (int j = 0; j < (int)atspMatrix[i].size(); j++)
		{
			std::cout << std::setw(4);
			std::cout << atspMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void ATSPMatrix::generateRandom(int size)
{
	atspMatrix.clear();
	nodes.clear();
	int number;
	dimension = size;
	for (int i = 0; i < dimension; i++) {
		std::vector<int> row;
		if (i != 0)
			nodes.push_back(i);
		for (int j = 0; j < dimension; j++) {
			number = rand() % 100;
			if (i == j)
				number = -1;
			row.push_back(number);
		}
		atspMatrix.push_back(row);
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
	nodes.clear();
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
			if (i == j)
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
		for (int i = 0; i < (int)nodes.size(); i++)
		{
			currentPath = calculatePath(nodes);
			//compare new path with the best path so far
			if (shortestPathLength == -1 || currentPath < shortestPathLength)
			{
				shortestPathNodes = nodes;
				shortestPathLength = currentPath;
			}
		}

	} while (std::next_permutation(nodes.begin(), nodes.end()));
	shortestPathLengthPrint = shortestPathLength;
	shortestPathNodesPrint = shortestPathNodes;
}

void ATSPMatrix::printShortestPath()
{
	std::cout << "Shortest path length: " << shortestPathLengthPrint;
	std::cout << "\nNodes: ";
	std::cout << "0->";
	for (const int x : shortestPathNodesPrint)
		std::cout << x << "->";
	std::cout << "0";
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

int ATSPMatrix::getStartingNode()
{
	return startingNode;
}

std::vector<std::vector<int>> ATSPMatrix::getMatrix()
{
	return atspMatrix;
}

ATSPMatrix::ATSPMatrix()
{
	dimension = 0;
	startingNode = 0;
	srand(time(NULL));
}


ATSPMatrix::~ATSPMatrix()
{
}
