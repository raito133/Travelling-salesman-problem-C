#pragma once
#include <vector>
#include "ATSPMatrix.h"
#include <queue>
class bnbSolver
{
	ATSPMatrix currentMatrix;

public:
	void solve();
	bnbSolver(ATSPMatrix &atspMatrix);
	~bnbSolver();
};

