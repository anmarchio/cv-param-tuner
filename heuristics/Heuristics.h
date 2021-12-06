#pragma once
#include "pch.h"
#include <math.h> 
#include <cstdlib>

int applyCVPipeline(int bestValue);
int getCost(int state);
int getNeighbors(int state);
void simulatedAnnealing(
	int param1,
	int param2,
	int param3,
	double *solution);