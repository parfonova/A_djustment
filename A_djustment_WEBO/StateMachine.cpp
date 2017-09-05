#include <string> 
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> 
#include "C:/Users/Lena/Documents/Visual Studio 2015/Projects/A_djustment_WEBO/A_djustment_WEBO/StateMachine.h"


using namespace std;
enum States { Idle = 0, Moving, in_Position, Error, Enable, Disable, Home };
States Zustand = Idle;

StateMachine::StateMachine(int Index)

{
	pAddr = &Addr;
	nPort = AdsPortOpen();
	GlobalError = AdsGetLocalAddress(pAddr);
	pAddr->port = 851;
	
	switch (Index)
	{
	case 1: Var_Error[15] = Var_Enable[15] = Var_CurPosition[14] = Var_GetWorkingMode[14] = Var_SetWorkingMode[14] =
		Var_Reset[15] = Var_Disable[15] = Var_Position[15] = Var_Velocity[15] =
		Var_Move_Start[15] = Var_Move_Stop[15] = Var_MovetoReference[15] = Var_SetAxisMode[15] =
		Var_is_Enable[15] = Var_is_Homed[15] = Var_in_Position[15] =
		Var_is_Moving[15] = Var_GetAxisMode[15] = '1';
		break;

	case 2: Var_Error[15] = Var_Reset[15] = Var_CurPosition[14] = Var_GetWorkingMode[14] = Var_SetWorkingMode[14] =
		Var_Enable[15] = Var_Disable[15] = Var_Position[15] = Var_Velocity[15]
		= Var_Move_Start[15] = Var_Move_Stop[15] = Var_MovetoReference[15] = Var_SetAxisMode[15]
		= Var_is_Enable[15] = Var_is_Homed[15] = Var_in_Position[15]
		= Var_is_Moving[15] = Var_GetAxisMode[15] = '2';
		break;
	case 3: Var_Error[15] = Var_Reset[15] = Var_CurPosition[14] = Var_GetWorkingMode[14] = Var_SetWorkingMode[14] =
		Var_Enable[15] = Var_Disable[15] = Var_Position[15] = Var_Velocity[15] =
		Var_Move_Start[15] = Var_Move_Stop[15] = Var_MovetoReference[15] =
		Var_SetAxisMode[15] = Var_is_Enable[15] = Var_is_Homed[15] = Var_in_Position[15] =
		Var_is_Moving[15] = Var_GetAxisMode[15] = '3';
		break;
	}

}


StateMachine::~StateMachine()
{
}


void StateMachine::Zustaende()
{	
	switch (Zustand) {

	case Idle:
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
		
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
		if (Data_is_Enable == true) { Zustand = Enable; }
		else if (Data_is_Enable == false) { Zustand = Disable; }
		else { Zustand = Error; }
				
		break;

	

	case Error:
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
		if (Data_Error = true) { Zustand = Error; }
		break;

	case Enable:
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Homed), &Hdl_is_Homed, sizeof(Var_is_Homed), &Var_is_Homed);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Homed, sizeof(Data_is_Homed), &Data_is_Homed);
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);
		if (Data_is_Moving == true) { Zustand = Moving;}
		else if (Data_is_Homed) { Zustand = Home;}
		else { Zustand = in_Position; }
		break;

	case Home:
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);
		if (Data_in_Position) { Zustand = in_Position; }
		else if (Data_is_Moving) { Zustand = Moving; }
		else { Zustand = Home;}
		break;

	case Moving:
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Homed), &Hdl_is_Homed, sizeof(Var_is_Homed), &Var_is_Homed);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Homed, sizeof(Data_is_Homed), &Data_is_Homed);
		if (Data_in_Position == true) { Zustand = in_Position; }
		else if (Data_is_Homed) { Zustand = Home; }
		else { Zustand = Moving; }
		break;


	case in_Position:
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Homed), &Hdl_is_Homed, sizeof(Var_is_Homed), &Var_is_Homed);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Homed, sizeof(Data_is_Homed), &Data_is_Homed);
		if (Data_is_Moving == true) { Zustand = Moving; }
		else if (Data_is_Homed) { Zustand = Home; }
		else { Zustand = in_Position; }
		break;

	case Disable:
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
		if (Data_is_Enable == true) { Zustand = Enable;}
		else if (Data_Error = true) { Zustand = Error;}
		break;
		

	default:
		{Zustand = Idle; }
	}


	//return Zustand;
}

//
//void StateMachine::Reset()
//{
//	//1. Schleife error -> reset
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
//	do
//	{
//		Data_Reset = true;
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
//		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
//	} while (Data_Error == false);
//}
//
//
//void StateMachine::MovingCheck()
//{
//	//2. Schleife is_Moving -> Moving_Stop
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Stop), &Hdl_Move_Stop, sizeof(Var_Move_Stop), &Var_Move_Stop);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Stop, sizeof(Data_Move_Stop), &Data_Move_Stop);
//
//	do
//	{
//		Data_Move_Stop = true;
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Stop), &Hdl_Move_Stop, sizeof(Var_Move_Stop), &Var_Move_Stop);
//		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Stop, sizeof(Data_Move_Stop), &Data_Move_Stop);
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
//	} while (Data_is_Moving == true);
//
//}
//
//
//
//
//
//void StateMachine::Homed()
//{
//	//4. Schleife isHomed -> Reference
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Homed), &Hdl_is_Homed, sizeof(Var_is_Homed), &Var_is_Homed);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Homed, sizeof(Data_is_Homed), &Data_is_Homed);
//
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_CurPosition), &Hdl_CurPosition, sizeof(Var_CurPosition), &Var_CurPosition);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_CurPosition, sizeof(Data_CurPosition), &Data_CurPosition);
//
//
//	if ((!Data_is_Homed) || (Data_CurPosition < 360))
//	{
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_MovetoReference), &Hdl_MovetoReference, sizeof(Var_MovetoReference), &Var_MovetoReference);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_MovetoReference, sizeof(Data_MovetoReference), &Data_MovetoReference);
//
//		Data_MovetoReference = true;
//		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_MovetoReference, sizeof(Data_MovetoReference), &Data_MovetoReference);
//		Sleep(1000);
//	}
//}
//
//void StateMachine::inPosition(double velocity, double position)
//{
//	//5. Schleife Position -> in_Position
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_CurPosition), &Hdl_CurPosition, sizeof(Var_CurPosition), &Var_CurPosition);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_CurPosition, sizeof(Data_CurPosition), &Data_CurPosition);
//
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Start), &Hdl_Move_Start, sizeof(Var_Move_Start), &Var_Move_Start);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Start, sizeof(Data_Move_Start), &Data_Move_Start);
//
//	do
//	{
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Velocity), &Hdl_Velocity, sizeof(Var_Velocity), &Var_Velocity);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Velocity, sizeof(Data_Velocity), &Data_Velocity);
//
//		Data_Velocity = velocity;
//		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Velocity, sizeof(Data_Velocity), &Data_Velocity);
//		Sleep(1000);
//
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Position), &Hdl_Position, sizeof(Var_Position), &Var_Position);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Position, sizeof(Data_Position), &Data_Position);
//		Data_Position = position;
//		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Position, sizeof(Data_Position), &Data_Position);
//		Sleep(1000);
//
//		Data_Move_Start = true;
//		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Start, sizeof(Data_Move_Start), &Data_Move_Start);
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);
//
//		Sleep(1000);
//
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetAxisMode, sizeof(Data_GetAxisMode), &Data_GetAxisMode);
//	} while (Data_in_Position == false);
//
//	// Release the handle of the PLC-variable
//	nErr_Enable = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(Hdl_Enable), &Hdl_Enable);
//	if (nErr_Enable) cerr << "Error: AdsSyncWriteReq: Enable " << nErr_Enable << '\n';//
//	if (nErr_Enable) cerr << "Error: AdsPortClose: Enable " << nErr_Enable << '\n';//
//	cout << " HSM is on Position 0 " << endl;
//}
//
//void StateMachine::HSM_AxisMode()
//
//{//Schleife GetAxisMode -> SetAxisMode -> Enable -> Error -> Reset
//
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_SetAxisMode), &Hdl_SetAxisMode, sizeof(Var_SetAxisMode), &Var_SetAxisMode);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_SetAxisMode, sizeof(Data_SetAxisMode), &Data_SetAxisMode);
//
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Enable), &Hdl_Enable, sizeof(Var_Enable), &Var_Enable);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
//
//	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
//	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
//
//	do
//	{
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_GetAxisMode), &Hdl_GetAxisMode, sizeof(Var_GetAxisMode), &Var_GetAxisMode);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetAxisMode, sizeof(Data_GetAxisMode), &Data_GetAxisMode);
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Disable), &Hdl_Disable, sizeof(Var_Disable), &Var_Disable);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Disable, sizeof(Data_Disable), &Data_Disable);
//		if (Data_GetAxisMode != 0)
//		{
//			Data_Disable = true;
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Disable, sizeof(Data_Disable), &Data_Disable);
//			Sleep(1000);
//		}
//
//		Data_SetAxisMode = 1;
//		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_SetAxisMode, sizeof(Data_SetAxisMode), &Data_SetAxisMode);
//		Sleep(1000);
//
//		do {
//			Data_Enable = true;
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
//			Sleep(1000);
//			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
//		} while (Data_is_Enable == false);
//
//
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
//
//		if (Data_Error == false)
//		{
//			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
//			Data_Reset = true;
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
//			Sleep(1000);
//		}
//	} while (Data_GetAxisMode != 1);
//}
//
//
//void StateMachine::WP_WorkingMode()
//{
//
//
//	// WP - WorkingMode
//	// 0 - Jog
//	// 1 - Manuell
//	// 2 - Automatisch
//
//	//Xx.WP Schleife GetAWorkingMode -> SetWorkingMode-> Enable->Error->Reset
//	do {
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_GetWorkingMode), &Hdl_GetWorkingMode, sizeof(Var_GetWorkingMode), &Var_GetWorkingMode);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetWorkingMode, sizeof(Data_GetWorkingMode), &Data_GetWorkingMode);
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_SetWorkingMode), &Hdl_SetWorkingMode, sizeof(Var_SetWorkingMode), &Var_SetWorkingMode);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_SetWorkingMode, sizeof(Data_SetWorkingMode), &Data_SetWorkingMode);
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Enable), &Hdl_Enable, sizeof(Var_Enable), &Var_Enable);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
//
//
//		switch (Data_GetWorkingMode)
//		{
//		case '0': Data_SetWorkingMode = 1;
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_SetWorkingMode, sizeof(Data_SetWorkingMode), &Data_SetWorkingMode);
//			Sleep(1000);
//
//			Data_Disable = true;
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Disable, sizeof(Data_Disable), &Data_Disable);
//			Sleep(1000);
//			do {
//				Data_Enable = true;
//				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
//				Sleep(1000);
//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
//			} while (Data_is_Enable == false);
//			break;
//
//		case '1':
//			break;
//
//		case '2': Data_SetWorkingMode = 1;
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_SetWorkingMode, sizeof(Data_SetWorkingMode), &Data_SetWorkingMode);
//			Sleep(1000);
//
//			Data_Disable = true;
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Disable, sizeof(Data_Disable), &Data_Disable);
//			Sleep(1000);
//			do {
//				Data_Enable = true;
//				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
//				Sleep(1000);
//				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
//			} while (Data_is_Enable == false);
//
//			break;
//		}
//
//		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
//		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
//
//		if (Data_Error == false)
//		{
//			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
//			Data_Reset = true;
//			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
//			Sleep(1000);
//
//		}
//	} while (Data_GetWorkingMode != 1);
//}
//
//
//void StateMachine::PortClose()
//{
//	// Close the communication port
//	GlobalError = AdsPortClose();
//}
