#include "pch.h"
#include "ATSPMatrix.h"


void ATSPMatrix::printMatrix()
{
	
	std::cout << "Name: " << name << ", dimension: " << dimension << std::endl;
	for (int i = 0; i < atspMatrix.size(); i++)
	{
		for (int j = 0; j < atspMatrix[i].size(); j++)
		{
			std::cout << std::setw(2);
			std::cout << atspMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void ATSPMatrix::loadFile(std::string fileName)
{
	std::ifstream load;
	load.open(fileName);
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
		for (int j = 0; j < dimension; j++) {
			load >> number;
			if (number == 9999)
				number = -1;
			row.push_back(number);
		}
		atspMatrix.push_back(row);
	}
	std::cout << "Loaded file: " << name << std::endl << "Dimension: " << dimension << std::endl;

}

ATSPMatrix::ATSPMatrix()
{
	dimension = 0;
}


ATSPMatrix::~ATSPMatrix()
{
}
