#include "pch.h"
#include "Node.h"


int Node::findMin(int row)
{
	int min = -1;
	int currentNumber;
	for (int i = 0; i < matrix.size(); i++)
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
	int calculateBound = 0;
	if (vertices.size() == 1)
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			calculateBound += findMin(i);
		}
		return calculateBound;
	}
	for (int i = 0; i<vertices.size()-1; i++)
		calculateBound += matrix[vertices[i]][vertices[i + 1]];
	for (int i = 0; i < matrix.size(); i++)
	{
		if (visitedNotLast(i))
			continue;
		calculateBound += findMin(i);
	}
	return calculateBound;
}

bool Node::visitedNotLast(int vertice)
{
	for (int i = 0; i < vertices.size() - 1; i++)
	{
		if (vertices[i] == vertice)
			return true;
	}
	return false;
}

bool Node::visited(int vertice)
{
	for (const int x : vertices)
		if (x == vertice)
			return true;
	return false;
}

Node::~Node()
{
}
