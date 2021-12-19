#include "pch.h"
#include "Heuristics.h"

void applyCVPipeline(double* bestValue, double* result)
{
	// Polynomial test function
	//  
	*result = 3 * pow(*bestValue, 2) +
		*bestValue -
		20;
	//return result;
}

double getCost(double* state)
{
	// Calculates cost of 
	// the argument state 
	// for your solution.
	double result = 0.0;
	applyCVPipeline(state, &result);
	return result;
}

double getNeighbors(double state)
{
	// Returns neighbors of 
	// the argument state 
	// for your solution.
	
	double fMin = 0.0;
	double fMax = 1.0;
	double f = (double)rand() / RAND_MAX;
	double delta = fMin + f * (fMax - fMin);
	//double delta = rand() % 4 * 1.0;
	if (rand() % 2 == 0)
	{
		state += delta;
	}
	else
	{
		state -= delta;
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
	double alpha = 0.1;

	double currentTemp = initialTemp;

	// Current Initial State
	double currentState = (double) (rand() % 10);
	double init = 0.0;
	solution = &init;
	*solution = getCost(&currentState);


	std::default_random_engine generator;
	std::uniform_real_distribution<double> rdist(0.0, 1.0);

	while(currentTemp > finalTemp)
	{
		// Get Neighbour of the current state
		double neighbor = getNeighbors(currentState);		

		double currentStateCost = getCost(&currentState);
		// Calculate difference between neighbor and current state
		double costDifference = currentStateCost - getCost(&neighbor);
				
		// If solution is met, stop
		if (currentStateCost >= -0.3 && currentStateCost <= 0.3)
		{
			std::cout << "Temp: " << currentTemp << "\n";
			std::cout << "Neighbor: " << neighbor << "\n";
			std::cout << "Current State: " << currentState << "\n";
			std::cout << "Current State Cost: " << currentStateCost << "\n";
			break;
		}

		// If solution is better, accept it
		if (costDifference > 0.0)
		{
			//*solution = getCost(&neighbor);
			currentState = neighbor;			
		} 
		else 
		{
			// if the new solution is not better, accept it with a prop of e^(-cost/temp)
			if(costDifference <= 0.0 || rdist(generator) < exp(- costDifference / currentTemp))
			{
				//*solution = getCost(&neighbor);
				currentState = neighbor;
			}
		}
		// Decrement the temperature
		currentTemp -= alpha;

		std::cout << "Temp: " << currentTemp << "\n";
		std::cout << "Neighbor: " << neighbor << "\n";
		std::cout << "Current State: " << currentState << "\n";
		std::cout << "Current State Cost: " << currentStateCost << "\n";
	}
}
