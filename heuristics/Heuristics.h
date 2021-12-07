#pragma once
#include "pch.h"
#include <math.h> 
#include <cstdlib>
#include <iostream>

void applyCVPipeline(double* bestValue, double* result);
double getCost(double* state);
double getNeighbors(double state);
void simulatedAnnealing(
	int param1,
	int param2,
	int param3,
	double *solution);