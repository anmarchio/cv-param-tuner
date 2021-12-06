#include "pch.h"
#include "Heuristics.h"

double applyCVPipeline(double bestValue)
{
	// Polynomial test function
	//  f(x)= 3x^2 + x + 1 
	double result = 3 * pow(bestValue, 2) +
		bestValue +
		1;
	return result;
}

double getCost(double state)
{
	// Calculates cost of 
	// the argument state 
	// for your solution.
	return applyCVPipeline(state);
}

double getNeighbors(double state)
{
	// Returns neighbors of 
	// the argument state 
	// for your solution.
	if (rand() % 2 == 0)
	{
		state++;
	}
	else
	{
		state--;
	}
	return state;
}

int max = 100;

void simulatedAnnealing(
	int param1,
	int param2,
	int param3,
	double *solution)
{
	// Generate an initial point
	//*best = rand() % 100;
	//int bestEvaluation = applyCVPipeline(*best);
	double initialTemp = 90.0;
	double finalTemp = .1;
	double alpha = 0.01;

	double currentTemp = initialTemp;

	// Current Initial State
	double currentState = (double) (rand() % 100);
	solution = getCost(currentState);

	while(currentTemp > finalTemp)
	{
		// Get Neighbour of the current state
		double neighbor = getNeighbors(currentState);

		// Calculate difference between neighbor and current state
		double costDifference = getCost(currentState) - getCost(neighbor);
				
		// If solution is better, accept it
		if (costDifference > 0)
		{
			solution = getCost(neighbor);
		} 
		else 
		{
			// if the new solution is not better, accept it with a prop of e^(-cost/temp)
			if((double) rand() < exp(costDifference / currentTemp))
			{
				solution = getCost(neighbor);
			}
		}
		// Decrement the temperature
		currentTemp -= alpha;
	}
}
