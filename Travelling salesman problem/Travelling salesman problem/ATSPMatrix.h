#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
class ATSPMatrix
{
	int dimension;
	std::string name;
	std::vector<std::vector<int>> atspMatrix;
	std::vector<int> nodes;
	std::vector<int> shortestPathNodesPrint;
	int startingNode = 0;
	int shortestPathLengthPrint;
	
public:
	void printMatrix();
	bool loadFile(std::string fileName);
	void bruteForce();
	void printShortestPath();
	std::string getName();
	int getDimension();
	int getStartingNode();
	int calculatePath(std::vector<int> nodes);
	int calculatePartialPath(std::vector<int> nodes);
	std::vector<std::vector<int>> getMatrix();
	ATSPMatrix();
	~ATSPMatrix();
};

