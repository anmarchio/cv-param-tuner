#pragma once
#include "pch.h"
#include <math.h> 
#include <cstdlib>
#include <iostream>
#include <random>

#include "Pipeline.h"

void applyCVPipeline(double* bestValue, double* result);
double getCost(double* state);
double getNeighbors(double state);
void initStateCostHist(double stateCostHist[], int size);
double getMaximumChange(
	double stateCostHist[],
	int stateCostHistSize,
	double currentStateCost);
void printStateHeader();
void printState(
	double currentTemp,
	double neighbor,
	double currentState,
	double currentStateCost,
	double maximumChange);
void simulatedAnnealing(
	string sourceImg,
	string groundTruthImg,
	double param1,
	double param2,
	double param3,
	double *solution);