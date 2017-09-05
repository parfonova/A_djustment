#pragma once

#ifndef UEYESTEAL_H
#define UEYESTEAL_H

#include "uEye.h"
#include "atlstr.h"
#include <opencv2/core/cuda.inl.hpp>

using namespace std;

class Steal
{
public:
	Steal()
	{
	}

	~Steal()
	{
	}

// camera functions
	INT InitCamera(HIDS *hCam, HWND hWnd);
	bool OpenCamera();
	void AllocateStealMemory();
	void GetMaxImageSize(INT *pnSizeX, INT *pnSizeY);
	void LoadParam();
	cv::Mat StealPic(double MotorAngle);
	void OnButtonSteal();
	void CloseCam();


private:
	// uEye-camera variables
	HIDS	m_hCam;			    // handle to camera
	HWND	m_hWndLive;	        // handle to live diplay window
	HWND	m_hWndSteal;	    // handle to steal image window
	INT		m_nColorMode;	    // Y8/RGB16/RGB24/RGB32
	INT		m_nBitsPerPixel;    // number of bits needed store one pixel
	INT     m_nSizeX;           // image size weight
	INT     m_nSizeY;           // image size height
	INT     m_nStealFormat;     // Pixel format for the steal operation 

	INT		m_lStealMemId;	    // camera memory - buffer ID
	char*	m_pcStealImgMem;    // camera memory - pointer to buffer
	CString m_SaveFileName;		//path name
	BOOL    m_bFirstTime;
	cv::Mat pic;

};
#endif