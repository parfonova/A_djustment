#include "CenterLB.h"
#include <iostream>
#include <ostream>
#include "vector"
#include <opencv/cv.h>

#include "windows.h"
#include <opencv2/imgproc.hpp>
#include <chrono>
#include <numeric>
#include <map>
#include <iomanip>
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
{
	//need Int variable for SWITCH-CASE
	int MotorAngleInt = (int)MotorAngle;

	switch (MotorAngleInt) {
	case 0:
		//Path to the image 
		image = imread("C:\\Users\\Lena\\Pictures\\LaserBeam_0.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 90:
		image = imread("C:\\Users\\Lena\\Pictures\\LaserBeam_90.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 1:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\1.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 2:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\2.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 3:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\3.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 4:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\4.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 5:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\5.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 6:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\6.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 7:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\7.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 8:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\8.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 9:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\9.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 10:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\10.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	case 11:
		image = cv::imread("C:\\Users\\Lena\\Pictures\\11.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		break;
	}
	return image;
}

cv::Mat CenterLB::Filter(double MotorAngle)
{
	image = ImageLoad(MotorAngle);

	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PXM_BINARY);
	compression_params.push_back(9);
	cv::Mat blr;
	
	//BLUR filtering - Reduce noise with a kernel 3x3
	cv::medianBlur(image, blr, 19);
	//cv::medianBlur(image, blr, 3);
	imwrite("D:/MASTERARBEIT/PICSBREICHT/2medianblur.bmp", blr, compression_params);

	cv::Mat imagebwthres;
	//Tresholding operation - From a grayscale image to create binary image
	threshold(blr, imagebwthres, 20, 255, CV_THRESH_BINARY);

	imwrite("D:/MASTERARBEIT/PICSBREICHT/3thres.bmp", imagebwthres, compression_params);

	//cv::Mat image_bw = image > 128;
	//imwrite("D:/MASTERARBEIT/PICSBREICHT/2SourceimageBW.jpg", image_bw);

	/////EROSION
	int erosionsize = 10;
	Mat el_eros = getStructuringElement(1, Size(2 * erosionsize + 1, 2 * erosionsize + 1), Point(erosionsize, erosionsize));
	erode(imagebwthres, erosion, el_eros);
	//cv::namedWindow("erosion", CV_WINDOW_AUTOSIZE);
	//cv::imshow("erosion", erosion);
	imwrite("D:/MASTERARBEIT/PICSBREICHT/4erosion.bmp", erosion, compression_params);

	////////CLOSING NEU//////////////////
	int closingsize1 = 7;
	Mat imageclose1;
	Mat el_close1 = getStructuringElement(1, Size(2 * closingsize1 + 1, 2 * closingsize1 + 1), Point(closingsize1, closingsize1));
	morphologyEx(erosion, imageclose1, MORPH_CLOSE, el_close1);
	//cv::namedWindow("CLOSE", CV_WINDOW_AUTOSIZE);
	//cv::imshow("CLOSE", imageclose);
	imwrite("D:/MASTERARBEIT/PICSBREICHT/7Neuimageclose.bmp", imageclose1, compression_params);
	
	///////////DILATION with Kernel 3///////////////////
	int dilationsize = 3;
	Mat el_dil = getStructuringElement(1, Size(2 * dilationsize + 1, 2 * dilationsize + 1), Point(dilationsize, dilationsize));
	dilate(imagebwthres, dilation, el_dil);
	imwrite("D:/MASTERARBEIT/PICSBREICHT/5dilation_with3.bmp", dilation, compression_params); //SAve the Pic

	//DILATION with Kernel 9
	int dilationsize1 = 9;
	Mat el_dil1 = getStructuringElement(1, Size(2 * dilationsize1 + 1, 2 * dilationsize1 + 1), Point(dilationsize1, dilationsize1));
	dilate(dilation, dilationNEU, el_dil1);
	imwrite("D:/MASTERARBEIT/PICSBREICHT/5NEUdilation_with9.bmp", dilationNEU, compression_params);
	
	//OPENING with Kernel 3
	int openingsize = 3;
	Mat el_open = getStructuringElement(1, Size(2 * openingsize + 1, 2 * openingsize + 1), Point(openingsize, openingsize));
	morphologyEx(imagebwthres, imageopen, MORPH_OPEN, el_open);
	imwrite("D:/MASTERARBEIT/PICSBREICHT/6imageopen.bmp", imageopen, compression_params);

	//CLOSING
	int closingsize = 5;
	Mat el_close = getStructuringElement(1, Size(2 * closingsize + 1, 2 * closingsize + 1), Point(closingsize, closingsize));
	morphologyEx(imagebwthres, imageclose, MORPH_CLOSE, el_close);
	morphologyEx(imageclose, imageclose, MORPH_CLOSE, el_close);
	imwrite("D:/MASTERARBEIT/PICSBREICHT/7imageclose.bmp", imageclose, compression_params);


	//Ausprobiert, was die andere Funktionen machen
	Mat sum_dil_close, or_dil_close, xor_dil_close;
	bitwise_and(dilation, imageclose, sum_dil_close);
	bitwise_or(dilation, imageclose, or_dil_close);
	bitwise_xor(dilation, imageclose, xor_dil_close);

	imwrite("D:/MASTERARBEIT/PICSBREICHT/sum_dil_close.bmp", sum_dil_close, compression_params);
	imwrite("D:/MASTERARBEIT/PICSBREICHT/or_dil_close.bmp", or_dil_close, compression_params);
	imwrite("D:/MASTERARBEIT/PICSBREICHT/xor_dil_close.bmp", xor_dil_close, compression_params);

	return dilationNEU; //Die Form von dieser Laserstrahlabbildung war am besten :)
}

double CenterLB::Diameter(double MotorAngle) // Equivalent Diameter
{
	cv::Mat im_canny;
	cv::Mat image = Filter(MotorAngle);
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PXM_BINARY);
	compression_params.push_back(9);
	int kernel_size = 5;
	int lowThres = 160;
	int highThres = 255;
	cv::Canny(image, im_canny, lowThres, highThres, kernel_size);  //edges
	cv::findContours(im_canny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0)); //Konturen
	const double PI = 3.141592653589793238463;
	double area = cv::contourArea(contours);
	double diameter = sqrt(4 * area / PI);
	return diameter;
}

vector<cv::Point2d> CenterLB::findCenterMassCenter(double MotorAngle)
{
	cv::Mat im_canny;
	cv::Mat image = Filter(MotorAngle);
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PXM_BINARY);
	compression_params.push_back(9);
	int kernel_size = 5;//war 3
	int lowThres = 160;
	int highThres = 255;
	//cv::Canny(dilation, im_canny, lowThres, highThres, kernel_size);
	cv::Canny(image, im_canny, lowThres, highThres, kernel_size); //edges
	imwrite("D:/MASTERARBEIT/PICSBREICHT/CANNY.bmp", im_canny, compression_params);
	cv::findContours(im_canny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0)); //Konturen

	///  Get contours: 
	vector<cv::Moments> mu(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}
	
	///  Get the mass centers:
	vector<cv::Point2d> CenterLaserBeam(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{
		CenterLaserBeam[i] = cv::Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);

	}

	// Im Vektor CenterLaserBeam war es oft so, dass es 2 fast identische Punkte ermittelt wurden, obwohl es nur ein Laserstrahl da ist.
	//Es erfolgt eine Überprüfung, ob da 1 Laserstrahl oder 2 sind(dementsprechend 2  oder 4 Points) und dann Mittelwertermittlung
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
			//cout << "CenterLB_Einbrand" << VectorCenter << endl;
			return VectorCenter;
			//cout << "Mass of 2 Objects" << VectorCenter << endl;
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
	
	//vector<int> compression_params;
	//compression_params.push_back(CV_IMWRITE_PXM_BINARY);
	//compression_params.push_back(9);

	//imwrite("D:/MASTERARBEIT/PICSBREICHT/CANNY.bmp", im_canny, compression_params);
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
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PXM_BINARY);
	compression_params.push_back(9);

	//cv::Mat image1 = imread("D:/MASTERARBEIT/PICSBREICHT/5NEUdilation_with9.bmp", 0);
	Mat image = Filter(MotorAngle);
	vector<double> VectorX(image.cols, 0);
	vector<double> VectorY(0, 0);
	// NADO PROVERIT for (int row = 0; row < image1.rows; row++)
	for (int row = 0; row < (image.rows-1); row++)
	{
		double coloredCols = 0;
		for (int col = 0; col < (image.cols-1); col++)
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
	//	cout << CenterX <<"," <<CenterY << "Integrierte CenterX und CenterY" << endl;
	return cv::Point2d(Center.x, Center.y);
}