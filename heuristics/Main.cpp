#pragma once
#include "pch.h"
#include <iostream>
#include <tchar.h>
#include <urlmon.h> //"urlmon.h: No such file or directory found"

#include "Heuristics.h"

#pragma comment(lib, "urlmon.lib")

using namespace std;

/*
	Missing args:
	- string: logfile path (txt)
	- array: input image paths
	- array: validation image paths
	- array: list of parameter values
	- func: objective function (filter method)
*/
int main()
{
	// 
	// Default parameters
	//
	// Set image path
	//string sourceImgPath = "C:/dev/cv-param-tuner/samples/Crack_(14415831884).jpg";
	string groundTruthImgPath = "C:/dev/cv-param-tuner/samples/binary.jpg";

	// Set source file URL
	const wchar_t* srcURL = L"https://upload.wikimedia.org/wikipedia/commons/1/13/Crack_%2814415831884%29.jpg";
	const wchar_t* destPath = L"C:/dev/cv-param-tuner/samples/Crack_(14415831884).jpg";
	HRESULT hr = URLDownloadToFile(NULL, srcURL, destPath, 0, NULL);
	// Convert wchar_t* to string
	wstring ws(destPath);
	string sourceImgPath(ws.begin(), ws.end());

	// Set image filter parameters
	double mainThreshold = 128.0;
	double gradientThreshold = 15.0;
	double minArea = 3000.0;

	cout << "Optimize CV Pipelines using Simulated Annealing\n";
	cout << "===============================================\n";

	// Run Simulated Annealing
	double solution = 0.0;

	simulatedAnnealing(
		sourceImgPath,
		groundTruthImgPath,
		128.0,
		15.0,
		3000.0,
		&solution);

	cout << "Final Solution: " << solution;
	cout << "\n";
}
