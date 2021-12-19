#pragma once
#include "pch.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/utility.hpp>

using namespace std;
using namespace cv;

class Pipeline
{
public:
	Pipeline();
	static Mat Run(Mat src, double mainThreshold, double gradientThreshold, double minArea);
	static void confusionMatrix(Mat m1, Mat m2, int* TP, int* TN, int* FP, int* FN);
	static double jaccardIndex(Mat m1, Mat m2);
	static double jaccardDistance(double jaccardIndex);

private:
	vector<string> operators;
	map<string, float> parameters;
};