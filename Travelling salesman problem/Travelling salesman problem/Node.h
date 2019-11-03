#pragma once
#include <vector>
#include <iostream>
class Node
{
	int findMin(int row);
	std::vector<std::vector<int>> matrix;
	bool visitedNotLast(int vertice);
public:
	std::vector<int> vertices;
	Node(std::vector<int> newVertices, int newVertice, std::vector<std::vector<int>> atspMatrix);
	bool visited(int vertice);
	int getBound();
	~Node();
};

