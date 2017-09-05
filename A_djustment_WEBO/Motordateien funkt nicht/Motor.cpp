#include "Motor.h"
#include <string> 
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> 
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsDef.h"
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsAPI.h"

using namespace std;


Motor::Motor(int Index) //hier erfolgt auch Änderung in Namen char, damit man alle Motoren ansteuern kann
{
	//Index.  to change a variablename
	switch (Index)
	{
	case 1: Var_Error[15] = Var_Enable[15] = Var_CurPosition[14] = Var_GetWorkingMode[15] = Var_SetWorkingMode[15] =
		Var_Reset[15] = Var_Disable[15] = Var_Position[15] = Var_Velocity[15] =
		Var_Move_Start[15] = Var_Move_Stop[15] = Var_MovetoReference[15] = Var_SetAxisMode[15] =
		Var_is_Enable[15] = Var_is_Homed[15] = Var_in_Position[15] =
		Var_is_Moving[15] = Var_GetAxisMode[15] = '1';
		break;

		//LinearTischmotor
	case 2: Var_Error[15] = Var_Reset[15] = Var_CurPosition[14] = Var_GetWorkingMode[15] = Var_SetWorkingMode[15] =
		Var_Enable[15] = Var_Disable[15] = Var_Position[15] = Var_Velocity[15]
		= Var_Move_Start[15] = Var_Move_Stop[15] = Var_MovetoReference[15] = Var_SetAxisMode[15]
		= Var_is_Enable[15] = Var_is_Homed[15] = Var_in_Position[15]
		= Var_is_Moving[15] = Var_GetAxisMode[15] = '2';
		break;

		//Hohlwellenmotor
	case 3: Var_Error[15] = Var_Reset[15] = Var_CurPosition[14] = Var_GetWorkingMode[15] = Var_SetWorkingMode[15] =
		Var_Enable[15] = Var_Disable[15] = Var_Position[15] = Var_Velocity[15] =
		Var_Move_Start[15] = Var_Move_Stop[15] = Var_MovetoReference[15] =
		Var_SetAxisMode[15] = Var_is_Enable[15] = Var_is_Homed[15] = Var_in_Position[15] =
		Var_is_Moving[15] = Var_GetAxisMode[15] = '3';
		break;

	default:
		Var_Error[15] = Var_Reset[15] = Var_CurPosition[14] = Var_GetWorkingMode[14] = Var_SetWorkingMode[14] =
			Var_Enable[15] = Var_Disable[15] = Var_Position[15] = Var_Velocity[15]
			= Var_Move_Start[15] = Var_Move_Stop[15] = Var_MovetoReference[15] = Var_SetAxisMode[15]
			= Var_is_Enable[15] = Var_is_Homed[15] = Var_in_Position[15]
			= Var_is_Moving[15] = Var_GetAxisMode[15] = '0';

	}
}


//bool Data Read
bool Motor::bRead(PAmsAddr pAddr, ULONG Handle, char Variable, bool Data) {
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Handle), &(Handle), sizeof(Variable), &Variable);
	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Handle, sizeof(Data), &Data);
	return Data;
}

//double Data Read
double  Motor::dRead(PAmsAddr pAddr, ULONG Handle, char Variable, double Data) {
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Handle), &(Handle), sizeof(Variable), &Variable);
	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Handle, sizeof(Data), &Data);
	return Data;
}

//USHORT Data Read
USHORT Motor::usRead(PAmsAddr pAddr, ULONG Handle, char Variable, USHORT Data) {
	//AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_GetAxisMode), &(Hdl_GetAxisMode), sizeof(Var_GetAxisMode), &Var_GetAxisMode);
	//AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetAxisMode, sizeof(Data_GetAxisMode), &Data_GetAxisMode);

	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Handle), &(Handle), sizeof(Variable), &Variable);
	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Handle, sizeof(Data), &Data);
	return Data;
}

//bool Data Write
void Motor::bWrite(PAmsAddr pAddr, ULONG Handle, char Variable, bool Data){
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Handle), &(Handle), sizeof(Variable), &Variable);
	AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Handle, sizeof(Data), &Data);
}

//double Data Write
void Motor::dWrite(PAmsAddr pAddr, ULONG Handle, char Variable, double Data) {
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Handle), &(Handle), sizeof(Variable), &Variable);
	AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Handle, sizeof(Data), &Data);
}
//USHORT Data Write
void Motor::usWrite(PAmsAddr pAddr, ULONG Handle, char Variable, USHORT Data) {
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Handle), &(Handle), sizeof(Variable), &Variable);
	AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Handle, sizeof(Data), &Data);
}


//Spindel modus wechseln im Hohlwellenmotor

	/*AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_GetAxisMode), &Hdl_GetAxisMode, sizeof(Var_GetAxisMode), &Var_GetAxisMode);
	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetAxisMode, sizeof(Data_GetAxisMode), &Data_GetAxisMode);*/
void Motor::SetHSMMode()
{	
	
	USHORT bollo = usRead(pAddr, Hdl_GetAxisMode, Var_GetAxisMode, Data_GetAxisMode);
	cout << bollo;

//	bool bollo5 = bRead(pAddr, Hdl_Enable, (char)Var_Enable, Data_Enable);
	//cout<< bollo5;


	/*while (Data_GetAxisMode != 1)
	{
		usRead(pAddr, Hdl_SetAxisMode, Var_SetAxisMode[30], Data_SetAxisMode);
		bRead(pAddr, Hdl_Enable, Var_Enable[25], Data_Enable);
		if ((usRead(pAddr, Hdl_GetAxisMode, Var_GetAxisMode[30], Data_GetAxisMode)) != 1)
		{
			bool ff = bRead(pAddr, Hdl_Disable, Var_Disable[26], Data_Disable);
			cout << ff;

			bWrite(pAddr, Hdl_Disable, Var_Disable[26], true);
			Sleep(1000);

			usWrite(pAddr, Hdl_SetAxisMode, Var_SetAxisMode[30], (USHORT)1);
			Sleep(1000);
		}
		do {
			bRead(pAddr, Hdl_Enable, Var_Enable[25], Data_Enable);

			bWrite(pAddr, Hdl_Enable, Var_Enable[25], true);
			Sleep(1000);
		} while (bRead(pAddr, Hdl_is_Enable, Var_is_Enable[28], Data_is_Enable) == false);

		do
		{
			bRead(pAddr, Hdl_Reset, Var_Reset[24], Data_Reset);
			Data_Reset = true;
			bWrite(pAddr, Hdl_Reset, Var_Reset[24], Data_Reset);
			Sleep(1000);
		} while ((bRead(pAddr, Hdl_Error, Var_Error[24], Data_Error)) == false);
	}*/
}


// WorkingMode
// 0 - Jog
// 1 - Manuell
// 2 - Automatisch
//  Disable -> GetAWorkingMode -> SetWorkingMode -> Enable -> Error -> Reset
void Motor::SetWorkingMode()
{
	do {
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_GetWorkingMode), &Hdl_GetWorkingMode, sizeof(Var_GetWorkingMode), &Var_GetWorkingMode);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetWorkingMode, sizeof(Data_GetWorkingMode), &Data_GetWorkingMode);

		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_SetWorkingMode), &Hdl_SetWorkingMode, sizeof(Var_SetWorkingMode), &Var_SetWorkingMode);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_SetWorkingMode, sizeof(Data_SetWorkingMode), &Data_SetWorkingMode);


		//Disable Motor
		Data_Disable = true;
		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Disable, sizeof(Data_Disable), &Data_Disable);
		Sleep(1000);
		do {
			switch (Data_GetWorkingMode)
			{
			case 0:

				Data_SetWorkingMode = 1;
				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_SetWorkingMode, sizeof(Data_SetWorkingMode), &Data_SetWorkingMode);
				Sleep(1000);
				break;

			case 1:
				break;

			case 2:
				Data_Disable = true;
				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Disable, sizeof(Data_Disable), &Data_Disable);
				Sleep(1000);
				Data_SetWorkingMode = 1;
				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_SetWorkingMode, sizeof(Data_SetWorkingMode), &Data_SetWorkingMode);
				Sleep(1000);
				break;
			default:
				cout << "Error. Working Mode konnte nicht identifiziert werden" << endl;
			}

			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Enable), &Hdl_Enable, sizeof(Var_Enable), &Var_Enable);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
			Data_Enable = true;
			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
			Sleep(1000);
			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
		}

		while (Data_is_Enable == false);


		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);

		if (Data_Error == false)
		{
			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
			Data_Reset = true;
			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
			Sleep(1000);
		}
	} while (Data_GetWorkingMode != 1);

	cout << "Initialisation was successful" << endl;
}


Motor::~Motor()
{
}



//in_Position beinhaltet State Machine
void Motor::inPosition(double velocity, double position)
{

	AdsPortOpen();
	AdsGetLocalAddress(pAddr);
	pAddr->port = 851;
	
	enum States { Idle = 0, Moving, in_Position, Error, Enable, Disable, Home };
	States Zustand = Idle;
	//
	//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_CurPosition), &Hdl_CurPosition, sizeof(Var_CurPosition), &Var_CurPosition);
	//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_CurPosition, sizeof(Data_CurPosition), &Data_CurPosition);
	//
	//	while (position != Data_CurPosition)
	//	{
	//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
	//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);
	//
	//		while (Zustand != Home)
	//		{
	//			switch (Zustand) {
	//
	//			case Idle:
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
	//
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
	//
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
	//
	//				//Motor stoppen
	//				if (Data_is_Moving == true)
	//				{
	//					Data_Move_Stop = true;
	//					AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Stop), &Hdl_Move_Stop, sizeof(Var_Move_Stop), &Var_Move_Stop);
	//					AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Stop, sizeof(Data_Move_Stop), &Data_Move_Stop);
	//
	//					Sleep(5000);
	//				}
	//
	//				if (Data_is_Enable == true) { Zustand = Enable; }
	//				else if (Data_is_Enable == false) { Zustand = Disable; }
	//				else { Zustand = Error; }
	//				break;
	//
	//			case Error:
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
	//				if (Data_Error == false)
	//				{
	//					Data_Reset = true;
	//
	//					AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
	//					AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
	//					Zustand = Idle;
	//				}
	//				break;
	//
	//			case Enable:
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
	//
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_MovetoReference), &Hdl_MovetoReference, sizeof(Var_MovetoReference), &Var_MovetoReference);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_MovetoReference, sizeof(Data_MovetoReference), &Data_MovetoReference);
	//
	//				//MovetoReference 
	//				Data_MovetoReference = true;
	//
	//				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_MovetoReference, sizeof(Data_MovetoReference), &Data_MovetoReference);
	//				Sleep(5000);
	//
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Homed), &Hdl_is_Homed, sizeof(Var_is_Homed), &Var_is_Homed);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Homed, sizeof(Data_is_Homed), &Data_is_Homed);
	//
	//				if (Data_is_Homed == true) { Zustand = Home; }
	//				else { Zustand = Enable; }
	//				break;
	//
	//			case Home:
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
	//
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);
	//
	//				if (Data_is_Moving) { Zustand = Moving; }
	//				else { Zustand = Home; }
	//				break;
	//
	//			case Moving:
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Homed), &Hdl_is_Homed, sizeof(Var_is_Homed), &Var_is_Homed);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Homed, sizeof(Data_is_Homed), &Data_is_Homed);
	//
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
	//
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
	//
	//				if (Data_is_Moving == true)
	//				{
	//					Data_Move_Stop = true;
	//					AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Stop), &Hdl_Move_Stop, sizeof(Var_Move_Stop), &Var_Move_Stop);
	//					AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Stop, sizeof(Data_Move_Stop), &Data_Move_Stop);
	//
	//					Sleep(5000);
	//				}
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
	//
	//				if (Data_is_Moving == true) { Zustand = Moving; }
	//				else if (Data_is_Homed) { Zustand = Home; }
	//				else if (Data_is_Enable == true) { Zustand = Enable; }
	//				break;
	//
	//			case Disable:
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);
	//
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
	//
	//				Data_Enable = true;
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Enable), &Hdl_Enable, sizeof(Var_Enable), &Var_Enable);
	//				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
	//
	//
	//				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
	//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
	//
	//				if (Data_is_Enable == true) { Zustand = Enable; }
	//				else if (Data_Error == true) { Zustand = Error; }
	//				else { Zustand = Disable; }
	//				break;
	//
	//			default:
	//			{Zustand = Idle; }
	//			}
	//		}
	//
	//	//velocity einstellen
	//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Velocity), &Hdl_Velocity, sizeof(Var_Velocity), &Var_Velocity);
	//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Velocity, sizeof(Data_Velocity), &Data_Velocity);
	//	Data_Velocity = velocity;
	//	AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Velocity, sizeof(Data_Velocity), &Data_Velocity);
	//	Sleep(1000);
	//
	//	//position einstellen
	//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Position), &Hdl_Position, sizeof(Var_Position), &Var_Position);
	//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Position, sizeof(Data_Position), &Data_Position);
	//	Data_Position = position;
	//	AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Position, sizeof(Data_Position), &Data_Position);
	//	Sleep(1000);
	//
	//	do
	//	{
	//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Start), &Hdl_Move_Start, sizeof(Var_Move_Start), &Var_Move_Start);
	//		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Start, sizeof(Data_Move_Start), &Data_Move_Start);
	//		Data_Move_Start = true;
	//		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Start, sizeof(Data_Move_Start), &Data_Move_Start);
	//
	//		Sleep(10000);
	//
	//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetAxisMode, sizeof(Data_GetAxisMode), &Data_GetAxisMode);
	//
	//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
	//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);
	//	} while (Data_in_Position == false);
	//
	//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_CurPosition), &Hdl_CurPosition, sizeof(Var_CurPosition), &Var_CurPosition);
	//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_CurPosition, sizeof(Data_CurPosition), &Data_CurPosition);
	//}
	//
	//	// Release the handle of the PLC-variable
	//	AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(Hdl_Enable), &Hdl_Enable);
	cout << " Hollowshaftmotor is in Position " << position << endl;
}


//
//void Motor::Reset()
//	{
//		//1. Schleife error -> reset
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
//
//		do
//		{
//			Data_Reset = true;
//
//			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
//			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
//			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
//		} while (Data_Error == false);
//	}
//
//void Motor::MovingCheck()
//	{
//		//2. Schleife is_Moving -> Moving_Stop
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Stop), &Hdl_Move_Stop, sizeof(Var_Move_Stop), &Var_Move_Stop);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Stop, sizeof(Data_Move_Stop), &Data_Move_Stop);
//
//		do
//		{
//			Data_Move_Stop = true;
//
//			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Stop), &Hdl_Move_Stop, sizeof(Var_Move_Stop), &Var_Move_Stop);
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Stop, sizeof(Data_Move_Stop), &Data_Move_Stop);
//
//			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
//			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
//		} while (Data_is_Moving == true);
//
//	}
//
//void Motor::Homed()
//	{
//		//4. Schleife isHomed -> Reference
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Homed), &Hdl_is_Homed, sizeof(Var_is_Homed), &Var_is_Homed);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Homed, sizeof(Data_is_Homed), &Data_is_Homed);
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_CurPosition), &Hdl_CurPosition, sizeof(Var_CurPosition), &Var_CurPosition);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_CurPosition, sizeof(Data_CurPosition), &Data_CurPosition);
//
//
//		if ((!Data_is_Homed) || (Data_CurPosition < 360))
//		{
//			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_MovetoReference), &Hdl_MovetoReference, sizeof(Var_MovetoReference), &Var_MovetoReference);
//			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_MovetoReference, sizeof(Data_MovetoReference), &Data_MovetoReference);
//
//			Data_MovetoReference = true;
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_MovetoReference, sizeof(Data_MovetoReference), &Data_MovetoReference);
//			Sleep(1000);
//		}
//	}



void Motor::PortClose()
{
	// Close the communication port
	AdsPortClose();
}

