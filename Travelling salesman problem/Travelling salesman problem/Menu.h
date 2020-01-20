#pragma once
#include <iostream>
#include <Windows.h>
#include "ATSPMatrix.h"
#include "bnbSolver.h"
#include <fstream>
#include "SimulatedAnnealing.h"
#include "GeneticAlgorithm.h"

#undef max


class Menu
{
	int choice;
	bool running;
	//menu displays
	void displayMain();
	void bfDispl();
	void pr1Displ();
	void pr2Displ();
	void pr2DisplDefault();
	void pr3Displ();
	void filDispl();
	void pr3DisplDefault();
	//test function
	void test();
	//time counting
	LARGE_INTEGER getTime();
	ATSPMatrix currentMatrix;
	bnbSolver* bnbsolv;
	SimulatedAnnealing* simulatedAnnealing;
	LARGE_INTEGER start, end, frequency;
	GeneticAlgorithm* geneticAlgorithm;

	
public:
	Menu();
	~Menu();
	bool isRunning();
	void run();

};

