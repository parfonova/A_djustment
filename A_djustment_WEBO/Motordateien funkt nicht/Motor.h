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
	Motor(int);//Konstruktor
	~Motor();
	
	AmsAddr  Addr;
	PAmsAddr pAddr = &Addr;
	
	bool bRead(PAmsAddr, ULONG, char, bool);
	double dRead(PAmsAddr, ULONG, char, double);
	USHORT usRead(PAmsAddr, ULONG, char, USHORT);

	void usWrite(PAmsAddr, ULONG, char, USHORT);
	void bWrite(PAmsAddr, ULONG, char, bool);
	void dWrite(PAmsAddr, ULONG, char, double);

	void SetHSMMode();

	//	void Reset();
	//	void MovingCheck();
	//	void Homed();
	void inPosition(double, double);
	void PortClose();
	
	//bool bRead(PAmsAddr pAddr, ULONG Handle, char Variable, bool Data);
	//double dRead(PAmsAddr pAddr, ULONG Handle, char Variable, double Data);
	void SetWorkingMode();

	//void WorkingMode();
	//void MotorsInit();
	//void HSM_AxisMode();

private:

	//Handle for all Variables in 
	ULONG     Hdl_CurPosition, Hdl_Velocity, Hdl_Position, Hdl_Enable, Hdl_Disable, Hdl_Reset, Hdl_Move_Start,
		Hdl_Move_Stop, Hdl_MovetoReference, Hdl_is_Enable, Hdl_is_Homed, Hdl_in_Position, Hdl_is_Moving, Hdl_Error,
		Hdl_GetAxisMode, Hdl_SetAxisMode, Hdl_GetWorkingMode, Hdl_SetWorkingMode;

	bool	  Data_Enable, Data_Disable, Data_Reset, Data_Move_Start, Data_Move_Stop, Data_MovetoReference,
		Data_is_Enable, Data_is_Homed, Data_in_Position, Data_is_Moving, Data_Error;
	double    Data_Position, Data_Velocity, Data_CurPosition;
	USHORT	  Data_SetAxisMode, Data_GetAxisMode, Data_SetWorkingMode, Data_GetWorkingMode;

	char  Var_CurPosition[39] = { "HMI_IO.Values[0].Position.Cur_Position" };
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

	void PortOpen(PAmsAddr);

};

#endif