#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
class ATSPMatrix
{
	int dimension;
	std::string name;
	std::vector<std::vector<int>> atspMatrix;
	
public:
	void printMatrix();
	void loadFile(std::string fileName);
	ATSPMatrix();
	~ATSPMatrix();
};

