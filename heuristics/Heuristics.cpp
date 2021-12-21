#include "pch.h"
#include "Heuristics.h"

Mat sourceImg;
Mat groundTruthImg;

void computePolynomialFunction(double* bestValue, double* result)
{
	// Polynomial test function
	//  
	*result = 3 * pow(*bestValue, 2) +
		*bestValue -
		20;
}

void applyCVPipeline(double* bestValue, double* result)
{
	// OpenCV filter function
	//  
	Mat prediction = Pipeline::RunThreshold(sourceImg, *bestValue, 15.0, 3000.0);
	*result = Pipeline::jaccardIndex(groundTruthImg, prediction);
}

double getCost(double* state)
{
	// Calculates cost of 
	// the argument state 
	// for your solution.
	double result = 0.0;
	applyCVPipeline(state, &result);
	return 1.0 - result;
}

void initStateCostHist(double stateCostHist[], int size)
{
	stateCostHist[size];
	for (int i = 0; i < size; i++)
	{
		if(i % 2 == 0)
			stateCostHist[i] = 1.0;
		else
			stateCostHist[i] = 0.0;
	}
}

double getMaximumChange(
	double stateCostHist[],
	int stateCostHistSize,
	double currentStateCost)
{
	double maxDelta = 0.0;
	for(int i = 0; i < stateCostHistSize; i++)
	{
		if (i < stateCostHistSize - 1)
			stateCostHist[i] = stateCostHist[i + 1];
		else
			stateCostHist[i] = currentStateCost;
		
		if(i > 0)
		{
			double delta = abs(stateCostHist[i] - stateCostHist[i - 1]);
			if (delta > maxDelta)
				maxDelta = delta;
		}
	}	
	return maxDelta;
}

void printStateHeader()
{
	std::cout << "Temp |";
	std::cout << "Neighbor |";
	std::cout << "Current State |";
	std::cout << "Current State Cost |";
	std::cout << "Maximum Change |\n";
}

void printState(
	double currentTemp,
	double neighbor,
	double currentState,
	double currentStateCost,
	double maximumChange)
{
	std::cout << currentTemp << " |";
	std::cout << neighbor << " |";
	std::cout << currentState << " |";
	std::cout << currentStateCost << " |";
	std::cout << maximumChange << " |\n";

}

double getNeighbors(double state)
{
	// Returns neighbors of 
	// the argument state 
	// for your solution.
	
	double fMin = 0.0;
	double fMax = 2.0;
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
	if (state < 0.0) state = 0.0;
	if (state > 255.0) state = 255;
	return state;
}

void simulatedAnnealing(
	string sourceImgPath,
	string groundTruthImgPath,
	double param1,
	double param2,
	double param3,
	double *solution)
{
	sourceImg = cv::imread(sourceImgPath);
	groundTruthImg = cv::imread(groundTruthImgPath);
	// Generate an initial point
	//*best = rand() % 100;
	//int bestEvaluation = applyCVPipeline(*best);
	double initialTemp = 90.0;
	double finalTemp = .1;
	double alpha = 0.1;

	double currentTemp = initialTemp;

	// Current Initial State
	double currentState = (double) (rand() % 200 + 50);
	double init = 0.0;
	solution = &init;
	*solution = getCost(&currentState);
	
	std::default_random_engine generator;
	std::uniform_real_distribution<double> rdist(0.0, 1.0);

	// Initialize termination criterion
	// for minimal maximum change
	// i. e. if change remains too little
	// over e. g. 10 iterations
	double stateCostHist[10];
	initStateCostHist(stateCostHist, 10);
	double minimalMaximumChange = 0.001;
	double maximumChange = 1.0;

	printStateHeader();
	// While loop
	// Terminates if
	// - finalTemp is met
	// - minimalMaximumChange is below 0.1 (or 10 %) over 10 generations
	while(currentTemp > finalTemp && maximumChange > minimalMaximumChange)
	{
		// Get Neighbour of the current state
		double neighbor = getNeighbors(currentState);		

		double currentStateCost = getCost(&currentState);
		// Calculate difference between neighbor and current state
		double costDifference = currentStateCost - getCost(&neighbor);
				
		// If solution is met, stop
		if (currentStateCost >= -0.3 && currentStateCost <= 0.3)
		{
			printState(currentTemp, neighbor, currentState, currentStateCost, maximumChange);
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
		
		printState(currentTemp, neighbor, currentState, currentStateCost, maximumChange);

		maximumChange = getMaximumChange(stateCostHist, 10, currentStateCost);
	}
}