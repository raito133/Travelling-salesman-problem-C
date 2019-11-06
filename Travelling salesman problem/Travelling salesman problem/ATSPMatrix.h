#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <random>

class ATSPMatrix
{
	int dimension;
	std::string name; //name of the file
	std::vector<std::vector<int>> atspMatrix; //matrix for storing the problem
	std::vector<int> nodes; //printing
	std::vector<int> shortestPathNodesPrint; //shortestPath for printing
	int startingNode = 0;
	int shortestPathLengthPrint;
	
public:
	void generateRandom(int size);
	void printMatrix();
	bool loadFile(std::string fileName);
	void bruteForce();
	void printShortestPath();
	std::string getName();
	int getDimension();
	int getStartingNode();
	int calculatePath(std::vector<int> nodes); //calculate the cost of the entire path
	int calculatePartialPath(std::vector<int> nodes); //calculating the cost of the path so far
	std::vector<std::vector<int>> getMatrix();
	ATSPMatrix();
	~ATSPMatrix();
};

