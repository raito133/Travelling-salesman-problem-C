#pragma once
#include <vector>
#include "ATSPMatrix.h"
#include <queue>
class bnbSolver
{
	ATSPMatrix currentMatrix;
	std::vector<int> shortestPathVertices; //vertices for printing
public:
	void solve();
	void printShortestPath();
	bnbSolver(ATSPMatrix &atspMatrix);
	~bnbSolver();
};

