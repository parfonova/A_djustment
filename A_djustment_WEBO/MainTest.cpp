////#define _WIN32_WINNT = 0x0551
////#define PORT "COM4" //default
////#define PORT1 "COM3"// Motor1 Ansteuerung
////#define PORT2 "COM4" // Motor2 Ansteuerung
////#define BOOST_AUTO_TEST_MAIN
////#include <boost/test/auto_unit_test.hpp>
////#include "BoostTextFixtures.hpp"
////std::ofstream redirect_report_to_file::os;
////BOOST_GLOBAL_FIXTURE(tee_cout_cerr_to_file_and_debug);
////BOOST_GLOBAL_FIXTURE(redirect_report_to_file);
////BOOST_GLOBAL_FIXTURE(log_settings);//Fehler? CLx

#pragma once
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#include <fstream>
#include <thread>
#include <opencv/cv.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc.hpp>

#include "CenterLB.h"
#include "Motor.h"
#include "XY_Mirror.h"
#include "uEyeSteal.h"
#include "PID.h"
#include "Math.h"
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsAPI.h"

double HSM_Position1 = 0.0; //Hohlwellenmotorposition 0 [Grad]
double HSM_Position2 = 90.0; //Hohlwellenmotorposition 90 [Grad]
double HSM_Position360 = 2; //für die Ermittlung des Wendelfehlers, deltaXY
double SPP;
double dis = 5; //distance für Stepmotor
double HSM_Velocity = 1000;
//
//cv::Point2d LaserBeamPosition;
//Steal Steal1;
//CenterLB CenterLB1;
//
//Motor Keilplatte(1);
//Motor LinearTisch(2);
//Motor Hohlwellenmotor(3);
//double HSM_Velocity = 1000;////Geschwindigkeit des HSM
using namespace std;

void MoveXYMirror(char Axis, double Distance)
{
	XYMirror XYMirror(Axis);
	XYMirror.Ready();
	XYMirror.JogMode();
	do
	{
		XYMirror.Distance(Distance);
		if (Distance < 0) { XYMirror.JogNegative(); }
		else
			XYMirror.JogPositive();
		XYMirror.InPosition();
	} while (!XYMirror.InPosition());
}

// Find the laser beam center with Demostratorsystem
cv::Point2d CenterLB_Demo(double MotorAngle) //zum Ausrechnen der Laserstrahlposition
{
	Steal Steal1;
	CenterLB CenterLB1;

	Steal1.StealPic(MotorAngle);
	CenterLB1.Filter(MotorAngle);

	//Differnet Methods of Laser beam position detection
	vector<cv::Point2d> findCenterMassCenter = CenterLB1.findCenterMassCenter(MotorAngle);
	cv::Point2d IntegrierterSchwerpunkt = CenterLB1.IntegrierterSchwerpunkt(MotorAngle);
	cv::Point2d ExtremPoints = CenterLB1.ExtremPoints(MotorAngle);

	ofstream textwrite;
	const char*	DateiName = "C://101.txt";
	textwrite.open(DateiName);
	textwrite << MotorAngle << "\t findCenterMassCenter \n" << findCenterMassCenter;
	textwrite << MotorAngle << "\t IntegrierterSchwerpunkt \n" << IntegrierterSchwerpunkt;
	textwrite << MotorAngle << "\t ExtremPoints " << ExtremPoints;

	//textwrite.close();

	
	cv::Point2d LaserBeamPosition;
	vector<cv::Point2d> LaserBeamPositionVec = CenterLB1.findCenterMassCenter(MotorAngle);
	cout << "LaserBeamPosition1" << LaserBeamPositionVec << endl;
	//AUszuKOMMENTIEREN LaserBeamPosition = LaserBeamPositionVec.at(1);// position 1 im Vector auslesen}

	return LaserBeamPosition;
}

//Function to find the Error.  Just for test. to delete later
double Abstand_ZS(double MotorAngle) {
	Steal Steal1;
	CenterLB CenterLB1;
	double Abstand; //Pixels
	vector<cv::Point2d> LaserBeamPositionZS = CenterLB1.findCenterMassCenter(MotorAngle);
	cout << "LaserBeamPositionZS" << LaserBeamPositionZS << endl;
	cv::Point2d delta = LaserBeamPositionZS.at(1) - LaserBeamPositionZS.at(2);
	Abstand = sqrt((delta.x)*(delta.x) + (delta.y)*(delta.y));
	return Abstand;
}

//Function to find the Error.  Just for test. to delete later
double CalculationSPP_Demo()
{
	const int m = 5; //Anzahl der Versuchen, um den SPPx, SPPy zu ermitteln
	double SPPxArr[m], SPPyArr[m];
	double SPPx, SPPy;
	double SumSPPx = 0, SumSPPy = 0;
	double StartStep = 500; //Anfangswert [Schritt]
	double scale = 12800;
	double Steps;
	cv::Point2d ist1, ist2; //Laserstrahlpositionen [pixel]
	cv::Mat pic1, pic2;
	double SD, SPP;
	double diff; //Differenz zwischen Zwei Punkten [pixel]
	double d; //Distanz für Schrittmotor [Schritte]
	double HSM_Position1 = 0.0;


	for (int n = 1; n < (m + 1); n++)
	{
		Motor Hohlwellenmotor(3);
		Hohlwellenmotor.GoToPosition(HSM_Position1, 50.0);
		//AUS ist1 = CenterLB_Demo(HSM_Position1);
		//Ansteuern M1 mit Relativen STEPS Schritten, Richtung – rechts

		d = StartStep * n / scale;
		while ((ist1.x != 0) || (ist1.y != 0))
		{
			if (ist1.x > 0.5*pic1.cols)
			{
				MoveXYMirror('x', -StartStep);
			}
			else
			{
				MoveXYMirror('x', StartStep);
			}
			//AUS		ist2 = CenterLB_Demo(HSM_Position1);
			Steps = (d * scale);
			if (abs(ist1.x - ist2.x) > abs(ist1.y - ist2.y))
			{
				diff = abs(ist1.x - ist2.x);
				SD = Steps / diff;
				SPPxArr[n - 1] = SD;
				SumSPPx = SumSPPx + SPPxArr[n - 1];
			}

			else
			{
				if (abs(ist1.x - ist2.x) == abs(ist1.y - ist2.y))
				{
					cout << "Die Parameter sind falsch eingestellt ";
					break;
				}
				diff = abs(ist1.y - ist2.y);
				SD = Steps / diff;
				SPPyArr[n - 1] = SD;
				SumSPPy = SumSPPy + SPPyArr[n - 1];
			}
			SPPx = SumSPPx / m;
			SPPy = SumSPPy / m;
		}
		SPP = SPPx > SPPy ? SPPx : SPPy;
		cout << "Schritte pro Pixel " << SPP << endl;
		Sleep(1000);
	}
	return SPP;
}

void WeBoAdjustment_Demo() //Ablauf der Justage an dem Demonstratorsystem
{
	cv::Point2d Point_0, Point_90;
	cv::Point2d ist, soll;
	cv::Point2d inc;
	Motor Hohlwellenmotor(3);

	double HSM_Position1 = 0.0; //Hohlwellenmotorposition 0 [Grad]
	double HSM_Position2 = 90.0; //Hohlwellenmotorposition 90 [Grad]

	//double HSM_Velocity = 1000;


	CalculationSPP_Demo();

	PID pidregler(0.5, 480, -480, 0.5, 0.01, 0.5);	//PID(double dt, double max, double min, double Kp, double Kd, double Ki);

	do
	{
		Hohlwellenmotor.GoToPosition(HSM_Velocity, HSM_Position1);
		Point_0 = CenterLB_Demo(HSM_Position1);

		Hohlwellenmotor.GoToPosition(HSM_Velocity, HSM_Position2);
		Point_90 = CenterLB_Demo(HSM_Position2);
		ist = Point_90;

		do
		{
			soll = (Point_0 + Point_90)*0.5;
			soll.x -= ist.x;
			soll.y -= ist.y;

			inc.x = pidregler.calculate(soll.x, ist.x);
			inc.y = pidregler.calculate(soll.y, ist.y);
			ist = { 0,0 };
			ist += inc;

			//Verfahren in x und y Richtung
			if (Point_90.x > Point_0.x)
			{
				MoveXYMirror('x', -inc.x);// X Mirror, Distance = + Wert in pos Richtung
			}
			else MoveXYMirror('x', -inc.x);// X Mirror, Distance = + Wert in neg Richtung


			if (Point_90.y > Point_0.y)
			{
				MoveXYMirror('y', -inc.y); // y Mirror, Distance = + Wert in pos Richtung
			}
			else MoveXYMirror('y', -inc.y); // y Mirror, Distance = + Wert in neg Richtung{} 


		} while ((abs(ist.x - soll.x) < 1) && (abs(ist.y - soll.y) < 1));

		cout << "ist.x \t" << ist.x << "val: \t\t" << ist.x << "\t " << "inc:\t" << inc.x << "x\t" << inc.y << "\n";
	}

	while ((abs(Point_0.x - Point_90.x) <= 1) && ((abs(Point_0.x - Point_90.x) <= 1)));

	cout << "Justage ist abgeschlossen" << endl;

	//  inc umrechnen in schritte und entscheiden in welche Richtung
	//	Ansteuerung des Motors Anstatt es ist.x += inc;
	//	Ist zu NULL, soll zu (soll.x - ist.x)
	//	Steal1.CloseCam();
}

vector<cv::Point2d> CenterLB_ZS(double MotorAngle)
{
	Steal Steal1;
	CenterLB CenterLB1;
	Steal1.StealPic(MotorAngle);
	
	//Different Methods of Laser beam position detection
	vector<cv::Point2d> LaserBeamPositionZS = CenterLB1.findCenterMassCenter(MotorAngle);

	cout << "LaserBeamPositionZS" << LaserBeamPositionZS << endl;
	return LaserBeamPositionZS;
}

cv::Point2d Delta_ZS(double MotorAngle) {
	Steal Steal1;
	CenterLB CenterLB1;
	vector<cv::Point2d> LaserBeamPositionZS = CenterLB1.findCenterMassCenter(MotorAngle);
	cv::Point2d delta = LaserBeamPositionZS.at(1) - LaserBeamPositionZS.at(2);
	delta.x = abs(delta.x);
	delta.y = abs(delta.y);
	return delta;
}

double CalculationSPP_ZS()
{
	double SumSPPx = 0, SumSPPy = 0;
	double StartStep = 100; //Anfangswert [Schritt]
	double scale = 12800;

	cv::Point ist1, ist2; //Laserstrahlpositionen [pixel]
	cv::Mat pic1, pic2;

	double diff; //Differenz zwischen Zwei Punkten [pixel]
	double d; //Distanz für Schrittmotor [Schritte]
	vector<cv::Point2d> Einbraende;
	//double HSM_Velocity = 1000;
	double HSM_Position360 = 2;
	Motor Hohlwellenmotor(3);
	Hohlwellenmotor.GoToPosition(HSM_Velocity,HSM_Position1);
	//1. Einbrand machen
	//AUS	ist1 = CenterLB_Demo(HSM_Position1);//Da gerade nur 1 Einbrand
	//Ansteuern M1 mit Relativen STEPS Schritten, Richtung – rechts
	d = StartStep / scale;
	if ((ist1.x != 0) || (ist1.y != 0))
	{
		if (ist1.x > 0.5*pic1.cols)
		{
			MoveXYMirror('x', -StartStep);
		}
		else
		{
			MoveXYMirror('x', StartStep);
		}

		//2. Einbrand machen - Laser ansteuern

		Einbraende = CenterLB_ZS(HSM_Position360);
		diff = abs(Einbraende.at(0).x - Einbraende.at(1).x);
		SPP = StartStep / diff;
	}
	else { std::cout << "Please adjust the system manual, Laserbeam could be found on the camera" << endl; }

	Sleep(1000);
	return SPP;
}

//double PIDControl()
//{
//	PID pidregler(0.5, 480, -480, 0.5, 0.01, 0.5);
//	cv::Point2d inc;
//	
//	/* Kp -  proportional gain
//	Ki -  Integral gain
//	Kd -  derivative gain
//	dt -  loop interval time
//	max - maximum value of manipulated variable
//	min - minimum value of manipulated variable*/
//	PID(double dt, double max, double min, double Kp, double Kd, double Ki);*/
//		do
//	
//	//Bild erfassen
//	//Steal1.AllocateStealMemory();
//	//Steal1.OnButtonStartLive();
//	//Steal1.OnButtonSteal();
//	//Steal1.StealPic(0);
//	////cv::Mat pic = cv::imread("C:\\Users\\Lena\\Pictures\\jhkj.bmp", CV_LOAD_IMAGE_GRAYSCALE);
//	//Steal1.StealPic(0);
//	//Steal1.OnButtonExit();
//	//CenterLB1.Filter(0);
//
//	////////Differnet Methods of Laser beam position detection
//	/*CenterLB1.findCenterMassCenter(0);
//	CenterLB1.IntegrierterSchwerpunkt(0);
//	Point_0 = CenterLB1.ExtremPoints(0);
//	*/
//
//	Point_0 = LBCenterLB((HSM_Position1);
//	Point_90 = LBCenterLB(HSM_Position2);
//	ist = Point_90;
//	do
//	{	soll = (Point_0 + Point_90)*0.5;
//		soll.x -= ist.x;
//		soll.y -= ist.y;
//
//	inc.x = pidregler.calculate(soll.x, ist.x);
//	inc.y = pidregler.calculate(soll.y, ist.y);
//	ist = { 0,0 };
//	ist += inc;
//	//Verfahren in x und y Richtung
//	} while ((abs(ist.x - soll.x) < 1) && (abs(ist.y - soll.y)<1));
//
//	cout << "ist.x \t" << ist.x << "val: \t\t" << ist.x << "\t " << "inc:\t" << inc.x << "x\t" << inc.y << "\n";
//	
//
//	while ((abs(Point_0.x - Point_90.x) <= 1) && ((abs(Point_0.x - Point_90.x) <= 1)));
//
//
//	cout << "Justage ist abgeschlossen" << endl;
//	// inc umrechnen in schritte und entscheiden in welche Richtung
//	//	Ansteuerung des Motors Anstatt es ist.x += inc;
//	//	Ist zu NULL, soll zu (soll.x - ist.x)
//	Steal1.CloseCam();
//
//}

//void WeBoAdjustment_ZS() //Dieses Teil soll noch weiter ueberarbeitet werden -> eventuell in MAIN. Case 1
//{
//	cv::Point2d Point_0, Point_90; //
//	cv::Point2d ist, soll;
//	cv::Point2d inc;
//	bool Fertig = false; // Wenn Fertig  = 1 dann ist die Justage abgeschlossen
//	vector<cv::Point2d> Einbraende;
//	cv::Point2d Distance; //in Motorschritten
//	cv::Point2d MinDistance(0.1, 0.1); //fuer den letzten Abschnitt der Justage
//	cv::Point2d DeltaXY(0, 0);//in Pixeln - Abstand zwischen zwei Einbraende 
//	cv::Point2d prev_DeltaXY(0, 0); //Delta(Abstand zwischen zwei Einbraende) im vorherigen Schritt in Pixeln 
//	CenterLB CenterLBforDiam;
//	double Diameter, SPP;
//	double prev_Diameter = 0.0;
//	double DiameterRefrenz;
//
//	//Ansteuerung Metallplatte verschieben ???
//
//	Motor Keilplatte(1);
//	Motor LinearTisch(2);
//	Motor Hohlwellenmotor(3);
//	//double HSM_Velocity = 1000;
//
//	SPP = CalculationSPP_ZS();
//
//	PID pidregler(0.5, 480, -480, 0.5, 0.01, 0.5); //PID(double dt, double max, double min, double Kp, double Kd, double Ki);
//
//	do
//	{
//		Hohlwellenmotor.GoToPosition(HSM_Velocity, HSM_Position1);
//
//		//Laserleistung niedrig einstellen
//		//Laser ansteuern - 1. Einbrand
//
//		Point_0 = CenterLB_Demo(HSM_Position1); //Demo nur ein Punkt da ist
//
//		Hohlwellenmotor.GoToPosition(HSM_Velocity, HSM_Position2);
//
//		//Laserleistung niedrig einstellen
//		//Laser ansteuern - 2. Einbrand
//
//		Einbraende = CenterLB_ZS(HSM_Position2); // sollte vector aus 2 Points/Einbrände sein 
//
//		//Bestimmung von Point_90
//		int n = Einbraende.size();
//		if (n == 2)
//		{
//			if (Point_90 == Einbraende.at(0))
//			{
//				Point_0 = Einbraende.at(1);
//			}
//			else
//			{
//				Point_0 = Einbraende.at(0);
//			}
//		}
//		else {
//			break;
//			cout << "Mehr als 2 Koordinaten erkannt" << endl;
//		}
//
//		//sie sollten gleich sein
//		soll = (Point_0 + Point_90)*0.5;
//		soll = (Einbraende.at(0) + Einbraende.at(1)) / 2;
//		//Methode, um die Richtung zu bestimmen
//		DeltaXY = Delta_ZS(HSM_Position360); //Pixel
//		prev_DeltaXY = DeltaXY;
//		Distance.x = SPP * 20;
//		Distance.y = SPP * 20;
//		MoveXYMirror('x', abs(Distance.x));
//		MoveXYMirror('y', abs(Distance.y));
//
//
//		//Fuer der Regler definieren wir IST_Delta = 0(Abweichung gleich 0)
//		while (!Fertig)
//		{
//			Hohlwellenmotor.GoToPosition(HSM_Velocity, HSM_Position1); //0 Grad Position
//															// Laserleistung niedrig einstellen
//															// Laser ansteuern - 1. Einbrand
//			Point_0 = CenterLB_Demo(HSM_Position1);				 // Demo da nur ein Punkt da ist
//			DiameterRefrenz = CenterLBforDiam.Diameter(HSM_Position1);
//			cout << DiameterRefrenz << endl;
//			Hohlwellenmotor.GoToPosition(HSM_Velocity, HSM_Position2); //90 Grad Position
//															// Laserleistung niedrig einstellen
//															// Laser ansteuern - 2. Einbrand
//			Einbraende = CenterLB_ZS(HSM_Position2);			 // sollte vector aus 2 Points sein
//
//			//Bestimmen welcher Einbrand als erster war
//			if (Point_90 == Einbraende.at(0))
//			{
//				Point_0 = Einbraende.at(1);
//			}
//			else
//			{
//				Point_0 = Einbraende.at(0);
//			}
//			//Hier sollte Ergebniss gleich sein
//			soll = (Point_0 + Point_90)*0.5;
//
//
//			size_t EinbraendeAnzahl = size(Einbraende); //bestimmen Anzahl der Objekten auf der Abbildung
//			switch (EinbraendeAnzahl)
//			{
//			case 2:
//
//				soll = (Einbraende.at(0) + Einbraende.at(1)) / 2; //Soll position ermitteln
//				DeltaXY = Delta_ZS(HSM_Position2); //Ermittlung der Abweichung Delta
//				//HSM_Position360 - nur als Beispiel.Es wird ein fertiges Bild benutzt
//
//				Distance = (SPP*DeltaXY / 2); //Ausrechnen der Distanz , die ein Schrittmotor verfahren soll
//
//		//	Bewegen des XYMirror auf  Distanz in x - und y - Richtung
//				if (DeltaXY.x < prev_DeltaXY.x) { Distance.x = Distance.x; }  // wenn nach der 
//				else { Distance.x = -Distance.x; }
//
//				MoveXYMirror('x', Distance.x);
//
//				if (DeltaXY.y < prev_DeltaXY.y) { Distance.y = Distance.y; }
//				else { Distance.y = -Distance.y; }
//
//				MoveXYMirror('y', Distance.y);
//
//				prev_DeltaXY = DeltaXY;
//
//				break;
//
//			case 1:
//				// wenn es um 2 Einbraende geht, die aber so nah zu einander sind, dass auf dem Bild nur ein Objekt bilden
//				//Methode mit der Größe
//				////Es wird die Größe der beiden Einbränden ermittelt, 
//				//die quasi auf einander liegen.
//			//	Die Justage ist abgeschlossen wenn dise Größe minimal ist.
//				prev_Diameter = CenterLBforDiam.Diameter(HSM_Position2);
//
//				if (Diameter < (1.1*DiameterRefrenz))
//				{
//					Fertig = true;
//					break;
//				}
//
//				MoveXYMirror('x', MinDistance.x);
//				Hohlwellenmotor.GoToPosition(HSM_Velocity, HSM_Position1); //0 Grad Position
////				Laserleistung niedrig einstellen
//				Hohlwellenmotor.GoToPosition(HSM_Velocity, HSM_Position1);													   //Laser ansteuern - 1. Einbrand
//
//				if (Diameter > prev_Diameter)
//
//				{
//					MoveXYMirror('y', MinDistance.y);
//				}
//				else {
//					MinDistance.x = -MinDistance.x;
//					MinDistance.y = -MinDistance.y;
//				}
//
//
//
//				//	Metallplatte verschieben um 1mm
//				Steal Steal1;
//				Steal1.CloseCam();
//			}
//		}
//	}
//
//}

//MAIN Programm
void main()
{
	//double HSM_Position1 = 0.0; //Hohlwellenmotorposition 0 [Grad]
	//double HSM_Position2 = 90.0; //Hohlwellenmotorposition 90 [Grad]
	//double HSM_Position360 = 2; //für die Ermittlung des Wendelfehlers, deltaXY
	//double SPP;
	double dis = 5; //distance für Stepmotor
	const char*	DateiName;

	cv::Point2d LaserBeamPosition;
	//Steal Steal1;
	
	//INT TRY = Steal1.OpenCamera();

	CenterLB CenterLB1;
	
	
	//Motor Keilplatte(1);
	//Motor LinearTisch(2);
	//Motor Hohlwellenmotor(3);
	//double HSM_Velocity = 1000;////Geschwindigkeit des HSM

	CenterLB_Demo(0);
	//CenterLB_Demo(5.0);

	//bool Adjustment_Demonstrator = true; //
	//		char type;
		//bool f = true;
		//do {
		//	cout << "Ist es die Justage am Demonstrator-System [y/n]" << endl;
		//	cin >> type;
		//	if ((type == 'n') || (type == 'N')) { Adjustment_Demonstrator = false; f = false; }
		//	else if ((type == 'y') || (type == 'Y')) {
		//		Adjustment_Demonstrator = true; f = false;
		//	}

		//} while (f);

		//if (Adjustment_Demonstrator) { //WeBoAdjustment_Demo()
		//	;
		//}
		//else {
		//	WeBoAdjustment_ZS();
		//}
	// CenterLB_Demo(1);
	// CenterLB_Demo(3);
	//CenterLB_ZS(HSM_Position2);
	//	Hohlwellenmotor.GoToPosition(15, 10);

		//vector<cv::Point2d>  Center = CenterLB_ZS(HSM_Position2);

		//cout << Center << endl;

	//long Error = AdsPortClose(); //Close the communication port
	//if (Error)  cerr << "Error in AdsPortClose: " << Error << endl;
	//Steal Steal1;
	//Steal1.CloseCam();

	system("pause");

//	Steal1.CloseCam();
	long Error = AdsPortClose();
	if (Error)  cerr << "Error in AdsPortClose: " << Error << endl;
           
	system("exec rm -r C:/Users/Lena/Pictures/"); //delete folder content
}

