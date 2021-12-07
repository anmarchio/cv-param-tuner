#include "pch.h"
#include "Main.h"

using namespace std;

int main()
{
	cout << "Optimize CV Pipelines using Simulated Annealing\n";
	cout << "===============================================\n";
	
	double solution = 0.0;
	
	simulatedAnnealing(
		10,
		20,
		30,
		&solution);

	cout << "Solution: " << solution;
	cout << "\n";
}
