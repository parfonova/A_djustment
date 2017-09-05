#include "CenterLB.h"
#include <iostream>
#include <ostream>
#include "vector"
#include <opencv/cv.h>

#include <opencv2/imgproc.hpp>

#include <numeric>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

CenterLB::CenterLB()
{
}

CenterLB::~CenterLB()
{
}
//Function for Loading of Image, if the path for the file specified is
cv::Mat CenterLB::ImageLoad(double MotorAngle)
{	//need Int variable for SWITCH-CASE
	int MotorAngleInt = (int)MotorAngle;

	switch (MotorAngleInt) {
	case 0:
		//Path to the image 
		image = imread("C:\\Pictures\\LaserBeam_0.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 90:
		image = imread("C:\\Pictures\\LaserBeam_90.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	default:
		image = cv::imread("C:\\Pictures\\1.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	}
	return image;
}

cv::Mat CenterLB::Filter(double MotorAngle)
{
	image = ImageLoad(MotorAngle); //Load the image from path

	//BLUR filtering - Reduce noise with a kernel 3x3
	cv::Mat blr;
	cv::medianBlur(image, blr, 19);

	//Tresholding operation - From a grayscale image to create binary image
	cv::Mat imagebwthres;
	threshold(blr, imagebwthres, 20, 255, CV_THRESH_BINARY);

	//EROSION
	int erosionsize = 10;
	Mat el_eros = getStructuringElement(1, Size(2 * erosionsize + 1, 2 * erosionsize + 1), Point(erosionsize, erosionsize));
	erode(imagebwthres, erosion, el_eros);

	//CLOSING
	int closingsize1 = 7;
	Mat imageclose1;
	Mat el_close1 = getStructuringElement(1, Size(2 * closingsize1 + 1, 2 * closingsize1 + 1), Point(closingsize1, closingsize1));
	morphologyEx(erosion, imageclose1, MORPH_CLOSE, el_close1);

	//DILATION 
	int dilationsize = 3;
	Mat el_dil = getStructuringElement(1, Size(2 * dilationsize + 1, 2 * dilationsize + 1), Point(dilationsize, dilationsize));
	dilate(imagebwthres, dilation, el_dil);

	//OPENING with Kernel 3
	int openingsize = 3;
	Mat el_open = getStructuringElement(1, Size(2 * openingsize + 1, 2 * openingsize + 1), Point(openingsize, openingsize));
	morphologyEx(imagebwthres, imageopen, MORPH_OPEN, el_open);

	//CLOSING
	int closingsize = 5;
	Mat el_close = getStructuringElement(1, Size(2 * closingsize + 1, 2 * closingsize + 1), Point(closingsize, closingsize));
	morphologyEx(imagebwthres, imageclose, MORPH_CLOSE, el_close);
	morphologyEx(imageclose, imageclose, MORPH_CLOSE, el_close);

	return dilation;
}

double CenterLB::Diameter(double MotorAngle) //Equivalent Diameter
{
	cv::Mat im_canny;
	cv::Mat image = Filter(MotorAngle);
	int kernel_size = 5;
	int lowThres = 160;
	int highThres = 255;
	cv::Canny(image, im_canny, lowThres, highThres, kernel_size);  //edges
	cv::findContours(im_canny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0)); //Contours
	const double PI = 3.141592653589793238463;
	double area = cv::contourArea(contours);
	double diameter = sqrt(4 * area / PI);
	return diameter;
}

vector<cv::Point2d> CenterLB::findCenterMassCenter(double MotorAngle)
{
	cv::Mat im_canny;
	cv::Mat image = Filter(MotorAngle);
	int kernel_size = 5;
	int lowThres = 160;
	int highThres = 255;
	cv::Canny(image, im_canny, lowThres, highThres, kernel_size); //edges
	cv::findContours(im_canny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0)); //contours

	vector<cv::Moments> mu(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	//Get the mass centers:
	vector<cv::Point2d> CenterLaserBeam(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{
		CenterLaserBeam[i] = cv::Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	if (size(CenterLaserBeam) == 2)
	{
		vector<cv::Point2d> VectorCenter;
		cv::Point2d CenterLB_Cameraimage = cv::Point2d((mu[0].m10 / mu[0].m00 + mu[1].m10 / mu[1].m00) / 2, (mu[0].m01 / mu[0].m00 + mu[1].m01 / mu[1].m00) / 2);
		cout << "CenterLB_Cameraimage" << CenterLB_Cameraimage << endl;
		VectorCenter.push_back(CenterLB_Cameraimage);

		return VectorCenter;
	}

	else {
		if (size(CenterLaserBeam) == 4)
		{
			vector<cv::Point2d> VectorCenter;
			cv::Point2d CenterLB_Einbrand1, CenterLB_Einbrand2;
			CenterLB_Einbrand1 = cv::Point2d((mu[0].m10 / mu[0].m00 + mu[1].m10 / mu[1].m00) / 2, (mu[0].m01 / mu[0].m00 + mu[1].m01 / mu[1].m00) / 2);
			CenterLB_Einbrand2 = cv::Point2d((mu[2].m10 / mu[2].m00 + mu[3].m10 / mu[3].m00) / 2, (mu[2].m01 / mu[2].m00 + mu[3].m01 / mu[3].m00) / 2);

			VectorCenter.push_back(CenterLB_Einbrand1);
			VectorCenter.push_back(CenterLB_Einbrand2);
			return VectorCenter;
		}
		else {
			cout << "Wrong Filtering Methods for this Application" << endl;
		}
	}
}

cv::Point2d CenterLB::ExtremPoints(double MotorAngle)
{
	Mat im_canny;
	Mat image = Filter(MotorAngle);
	cv::Point2d Center;
	cv::Canny(image, im_canny, 160, 255, 3);
	cout << "pause" << endl;

	cv::findContours(im_canny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	auto minX = NULL;
	auto minY = NULL;
	auto maxX = NULL;
	auto maxY = NULL;

	for (size_t i = 0; i < contours.size(); i++)
	{
		for (size_t j = 0; j < contours[i].size(); j++)
		{
			int x = contours[i][j].x;
			int y = contours[i][j].y;

			if (minX == NULL || x < minX)
			{
				minX = x;
			}
			if (maxX == NULL || x > maxX)
			{
				maxX = x;
			}
			if (minY == NULL || y < minY)
			{
				minY = y;
			}
			if (maxY == NULL || y > maxY)
			{
				maxY = y;
			}
		}
	}
	Center.x = (maxX + minX) / 2;
	Center.y = (maxY + minY) / 2;
	cvWaitKey(0);
	return Center;
}

cv::Point2d CenterLB::IntegrierterSchwerpunkt(double MotorAngle)
{
	cv::Point2d Center;
	cv::Mat image = Filter(MotorAngle);
	vector<double> VectorX(image.cols, 0);
	vector<double> VectorY(0, 0);

	for (int row = 0; row < image.rows; row++)
	{
		double coloredCols = 0;
		for (int col = 0; col < image.cols; col++)
		{
			int pixelValue = image.at<uchar>(row, col);

			if (pixelValue >= 200)
			{
				coloredCols += 1;
				VectorX.at(col) = VectorX.at(col) + 1;
			}
		}
		VectorY.push_back(coloredCols);
	}

	double sumVertical = accumulate(VectorX.begin(), VectorX.end(), 0);
	double sumHorizontal = accumulate(VectorY.begin(), VectorY.end(), 0);
	if ((sumHorizontal != sumVertical) || (sumHorizontal == 0))
	{
		cout << "Error counting pixels" << endl;
		cvWaitKey(0);
	}

	double MeanValuePixels = sumVertical / 2;
	double sumY = 0;
	double sumX = 0;
	int itY;
	int itX;

	for (itX = 0; itX < sumHorizontal; itX++)
	{
		sumX += VectorX.at(itX);
		Center.x = itX;
		if (sumX >= MeanValuePixels)  break;
	}

	for (itY = 0; itY < sumVertical; itY++)
	{
		sumY += VectorY.at(itY);
		Center.y = itY;
		if (sumY >= MeanValuePixels) break;
	}
	return cv::Point2d(Center.x, Center.y);
}