#include "pch.h"
#include "ATSPMatrix.h"


void ATSPMatrix::printMatrix()
{
	
	if (dimension == 0)
		std::cout << "No file is loaded\n";
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

bool ATSPMatrix::loadFile(std::string fileName)
{
	std::ifstream load;
	load.open(fileName);
	if (!load.is_open())
	{
		return false;
	}
	atspMatrix.clear();
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

	load.close();
	return true;

}

std::string ATSPMatrix::getName()
{
	return name;
}

int ATSPMatrix::getDimension()
{
	return dimension;
}

ATSPMatrix::ATSPMatrix()
{
	dimension = 0;
}


ATSPMatrix::~ATSPMatrix()
{
}
