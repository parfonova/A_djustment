#pragma once
#ifndef CENTERLB_H
#define CENTERLB_H

#include <map>
#include "uEyeSteal.h"
#include <opencv2/core/cuda.inl.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/core/mat.hpp>

using namespace std;

class CenterLB
{	
public: 
	CenterLB();
	~CenterLB();
	
	
	cv::Mat ImageLoad(double MotorAngle);
	cv::Mat Filter(double MotorAngle);
	double Diameter(double MotorAngle);

	vector<cv::Point2d> findCenterMassCenter(double MotorAngle);
	cv::Point2d ExtremPoints(double MotorAngle);
	cv::Point2d IntegrierterSchwerpunkt(double MotorAngle);

private:
	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;
	cv::Mat image;
	cv::Mat imageopen;
	cv::Mat erosion;
	cv::Mat dilation;
	cv::Mat imageclose;
	cv::Mat dilationNEU;
};

#endif //CENTERLB_H
