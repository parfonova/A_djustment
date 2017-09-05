#pragma once
#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <string>
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsDef.h"
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsAPI.h"

using namespace std;

class Motor
{
public:
	// übersichtlicher ist es, wenn, neben dem Datentyp, die Namen auch direkt da sind 
	Motor(int Index);
	~Motor();

	void GoToPosition(double velocity, double position);
	void PortClose();
	void Reset();
	void MovingCheck();
	void Homed();

private:
	AmsAddr   Addr;
	PAmsAddr  pAddr;
	/*long	    nErr_CurPosition,
	nErr_Disable,
	nErr_Enable,
	nErr_Reset,
	nErr_Position,
	nErr_Velocity,
	nErr_Move_Start,
	nErr_Move_Stop,
	nErr_MovetoReference,
	nErr_SetAxisMode,
	nErr_is_Enable,
	nErr_is_Homed,
	nErr_in_Position,
	nErr_Error,
	nErr_is_Moving,
	nErr_GetAxisMode,
	nErr_GetWorkingMode,
	nErr_SetWorkingMode;*/

	//Handle for all Variables in 
	ULONG     Hdl_CurPosition, Hdl_Velocity, Hdl_Position, Hdl_Enable, Hdl_Disable, Hdl_Reset, Hdl_Move_Start,
			  Hdl_Move_Stop, Hdl_MovetoReference, Hdl_is_Enable, Hdl_is_Homed, Hdl_in_Position, Hdl_is_Moving, Hdl_Error,
			  Hdl_GetAxisMode, Hdl_SetAxisMode, Hdl_GetWorkingMode, Hdl_SetWorkingMode;
	bool	  Data_Enable, Data_Disable, Data_Reset, Data_Move_Start, Data_Move_Stop, Data_MovetoReference,
			  Data_is_Enable, Data_is_Homed, Data_in_Position, Data_is_Moving, Data_Error;
	double    Data_Position, Data_Velocity, Data_CurPosition;
	USHORT	  Data_SetAxisMode, Data_GetAxisMode, Data_SetWorkingMode, Data_GetWorkingMode;

	char  Var_CurPosition[39] = { "HMI_IO.Values[0].Position.Cur_Position" };;
	char  Var_SetPosition[39] = { "HMI_IO.Values[0].Position.Set_Position" };
	char  Var_GetAxisMode[30] = { "HMI_IO.Befehle[0].GetAxisMode" };
	char  Var_SetAxisMode[30] = { "HMI_IO.Befehle[0].SetAxisMode" };
	char  Var_Reset[24] = { "HMI_IO.Befehle[0].Reset" };
	char  Var_Error[24] = { "HMI_IO.Befehle[0].Error" };
	char  Var_Enable[25] = { "HMI_IO.Befehle[0].Enable" };
	char  Var_Disable[26] = { "HMI_IO.Befehle[0].Disable" };
	char  Var_Position[27] = { "HMI_IO.Befehle[0].Position" };
	char  Var_Velocity[27] = { "HMI_IO.Befehle[0].Velocity" };
	char  Var_Move_Start[29] = { "HMI_IO.Befehle[0].Move_Start" };
	char  Var_Move_Stop[28] = { "HMI_IO.Befehle[0].Move_Stop" };
	char  Var_MovetoReference[34] = { "HMI_IO.Befehle[0].MovetoReference" };
	char  Var_is_Homed[27] = { "HMI_IO.Befehle[0].is_Homed" };
	char  Var_is_Enable[28] = { "HMI_IO.Befehle[0].is_Enable" };
	char  Var_in_Position[30] = { "HMI_IO.Befehle[0].in_Position" };
	char  Var_is_Moving[28] = { "HMI_IO.Befehle[0].is_Moving" };
	char  Var_GetWorkingMode[33] = { "HMI_IO.Befehle[0].GetWorkingMode" };
	char  Var_SetWorkingMode[33] = { "HMI_IO.Befehle[0].SetWorkingMode" };
	
};


#endif

	/*char  Var_CurPosition[39];
	char  Var_SetPosition[39];
	char  Var_GetAxisMode[30];
	char  Var_SetAxisMode[30];
	char  Var_Reset[24];
	char  Var_Error[24];
	char  Var_Enable[25];
	char  Var_Disable[26];
	char  Var_Position[27];
	char  Var_Velocity[27];
	char  Var_Move_Start[29];
	char  Var_Move_Stop[28];
	char  Var_MovetoReference[34];
	char  Var_is_Homed[27];
	char  Var_is_Enable[28];
	char  Var_in_Position[30];
	char  Var_is_Moving[28];
	char  Var_GetWorkingMode[33];
	char  Var_SetWorkingMode[33];
		*/