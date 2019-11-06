#include "pch.h"
#include "Node.h"


int Node::findMin(int row)
{
	//finds the minimal number in a given row
	int min = -1;
	int currentNumber;
	for (int i = 0; i < (int)matrix.size(); i++)
	{
		if (matrix[row][i] == -1)
			continue;
		currentNumber = matrix[row][i];
		if (min > currentNumber || min == -1)
			min = currentNumber;
		
	}
	return min;
}

std::vector<int> Node::getVertices()
{
	return vertices;
}

Node::Node(std::vector<int> newVertices, int newVertice, std::vector<std::vector<int>> &atspMatrix)
{
	vertices = newVertices;
	vertices.push_back(newVertice);
	matrix = atspMatrix;
}


int Node::getBound()
{
	//calculates the minimal path cost that could emerge from this node
	//adds traversed edges cost and minimal cost of edges that havent been traversed yet
	int calculateBound = 0;
	//case if there is only one vertice
	if (vertices.size() == 1)
	{
		for (int i = 0; i < (int)matrix.size(); i++)
		{
			calculateBound += findMin(i);
		}
		return calculateBound;
	}
	//adds traversed edges
	for (int i = 0; i<(int)vertices.size()-1; i++)
		calculateBound += matrix[vertices[i]][vertices[i + 1]];
	//adds not-traversed minimal edges
	for (int i = 0; i < (int)matrix.size(); i++)
	{
		if (visitedNotLast(i))
			continue;
		calculateBound += findMin(i);
	}
	return calculateBound;
}

bool Node::visitedNotLast(int vertice)
{
	for (int i = 0; i < (int)vertices.size() - 1; i++)
	{
		if (vertices[i] == vertice)
			return true;
	}
	return false;
}

bool Node::visited(int vertice)
{
	//returns if this node uses vertice in the path
	for (const int x : vertices)
		if (x == vertice)
			return true;
	return false;
}

Node::~Node()
{
}
