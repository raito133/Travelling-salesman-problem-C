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
	int calculatePath(std::vector<int> nodes);
	int startingNode = 0;
public:
	void printMatrix();
	bool loadFile(std::string fileName);
	void bruteForce();
	std::string getName();
	int getDimension();
	ATSPMatrix();
	~ATSPMatrix();
};

