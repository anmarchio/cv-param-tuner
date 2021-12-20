#include "pch.h"
#include "Pipeline.h"

Pipeline::Pipeline() {}

Mat Pipeline::Run(Mat src, double mainThreshold = 128.0, double gradientThreshold = 15.0, double minArea = 3000.0) {
	// Read image
	//Mat src = imread(imgPath, IMREAD_COLOR);

	// Show image
	string window_name = "Filter Pipeline";
	/*namedWindow(window_name, 0);
	resizeWindow(window_name, cv::Size(src.cols, src.rows));
	imshow(window_name, src);*/

	// Check if image is loaded correctly
	if (src.empty())
	{
		cout << "Error opening image.";
		return Mat();
	}

	GaussianBlur(src, src, Size(3, 3), 0.0);

	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	// Detect Roving
	Mat dst;
	//threshold(gray, dst, 200.0, 255.0, 0);
	threshold(gray, dst, mainThreshold, 255.0, 0);
	imshow(window_name, dst);
		
	//Sobel edge filters
	
	Mat grad_x, grad_y;
	int ddepth = CV_16S;
	int ksize = 3;
	double scale = 1.0;
	double delta = 0.0;
	// Gradient X
	Sobel(gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
	// Gradient Y
	Sobel(gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);

	Mat abs_grad_x, abs_grad_y;
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);

	// Mat grad;
	//addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0.0, grad);
	//imshow(window_name, grad);

	// filter image with threshold
	Mat thresh1;
	threshold(abs_grad_y, thresh1, gradientThreshold, 255.0, THRESH_BINARY);

	// apply dilation
	Mat kernel;
	kernel.ones(Size(3, 3), UINT8_MAX);
	Mat closing;
	morphologyEx(thresh1, closing, MORPH_CLOSE, kernel);

	// remove blobs
	vector<vector<Point>> contours;
	Mat closing_copy;
	closing.copyTo(closing_copy);
	findContours(closing_copy, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
	//double min_area = 3000.0;
	vector<vector<Point>> savedContours;
	for (vector<Point>cnt : contours)
	{
		double area = contourArea(cnt);
		if (area >= minArea)
		{
			savedContours.push_back(cnt);
		}
	}

	// Draw contours in red channel
	Mat mask(Size(src.cols, src.rows), CV_8SC3);
	drawContours(mask, savedContours, -1, Scalar(0, 0, 255), 3);

	// Add Image
	//Mat result;
	//add(src, mask, result);
	drawContours(src, savedContours, -1, Scalar(0, 0, 255), 3);

	//imshow(window_name, src);
	//waitKey(0);

	return mask;
}

/////////////////////////
// Similarity Metrics
/////////////////////////

void Pipeline::confusionMatrix(Mat m1, Mat m2, int* TP, int* TN, int* FP, int* FN)
{
	/*
		TP: True Positives
		TN: True Negatives
		FP: False Positives
		FN: False Negatives
	*/
	// Loop through Mat to find confusion matrix
	*TP = 0;
	*TN = 0;
	*FP = 0;
	*FN = 0;
	for (int r = 0; r < m1.rows; r++)
	{
		for (int c = 0; c < m2.cols; c++)
		{
			Vec3b zero = Vec3b(0, 0, 0);
			Vec3b one = Vec3b(255, 255, 255);
			// TP: m1 and m2 == 1
			if (m1.at<Vec3b>(r, c) == one && m2.at<Vec3b>(r, c) == one)
				*TP++;
			// TN: m1 and m2 == 0
			if (m1.at<Vec3b>(r, c) == zero && m2.at<Vec3b>(r, c) == zero)
				*TN++;
			// FP: m1 == 0 while m2 == 1
			if (m1.at<Vec3b>(r, c) == zero && m2.at<Vec3b>(r, c) == one)
				*FP++;
			// FN: m1 == 1 and m2 == 0
			if (m1.at<Vec3b>(r, c) == one && m2.at<Vec3b>(r, c) == zero)
				*FN++;
		}
	}
}

// Function to return the Jaccard index of two sets
double Pipeline::jaccardIndex(Mat m1, Mat m2)
{
	/*
		Definition:
		Jaccard Index = TP / (TP + FP + FN)
		m1 defines the groundtruth,
		m2 defines the prediction
	*/
	int TP = 0;
	int TN = 0;
	int FP = 0;
	int FN = 0;

	int* TPptr = &TP;
	int* TNptr = &TN;
	int* FPptr = &FP;
	int* FNptr = &FN;

	confusionMatrix(m1, m2, TPptr, TNptr, FPptr, FNptr);
	// Calculate the Jaccard index
	double jaccardInd = *TPptr * 1.0 / (*TPptr + *FPptr + *FNptr) * 1.0;
	return jaccardInd;
}

// Function to return the Jaccard distance
double Pipeline::jaccardDistance(double jaccardIndex)
{
	// Calculate the Jaccard distance
	// using the formula
	double jaccardDist = 1 - jaccardIndex;

	// Return the Jaccard distance
	return jaccardDist;
}