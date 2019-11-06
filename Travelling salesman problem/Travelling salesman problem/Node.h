#pragma once
#include <vector>
#include <iostream>
class Node
{
	int findMin(int row); //find minimal edge cost of a given row
	std::vector<std::vector<int>> matrix; //matrix for bound calculation
	bool visitedNotLast(int vertice);
	std::vector<int> vertices;
public:
	std::vector<int> getVertices();
	Node(std::vector<int> newVertices, int newVertice, std::vector<std::vector<int>> &atspMatrix);
	bool visited(int vertice);
	int getBound(); //calculate Bound
	~Node();
};

