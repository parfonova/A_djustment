#pragma once
#ifndef XY_MIRROR_H
#define XY_MIRROR_H

#include <iostream>
#include <windows.h>
#include <chrono>
#include <string>
#include <conio.h>
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsDef.h"
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsAPI.h"


using namespace std;

class XYMirror
{
public:

	XYMirror(char Axis);
	~XYMirror();
	AmsAddr   Addr;
	PAmsAddr  pAddr;
	void Reset();
	void Ready();
	void JogMode();
	void Distance(double dis); // Distance eingeben
	void JogNegative();
	void JogPositive();
	bool InPosition();

private:
	long	  GlobalError, nPort;
		
	//Handle for all Variables in 
	ULONG    Hdl_Enable,Hdl_Stop,Hdl_Reset, Hdl_Home,Hdl_JogDistance, Hdl_JogPositive,
			 Hdl_JogNegative, Hdl_JogMode, Hdl_Enabled, Hdl_Ready, Hdl_Homed,Hdl_InPosition, Hdl_Moving, Hdl_TargetVelocity;
	
	bool	 Data_Enable, Data_Disable, Data_Reset, Data_Move_Start, Data_Move_Stop, Data_MovetoReference,
			 Data_Enabled, Data_is_Homed, Data_InPosition, Data_is_Moving, Data_Ready, Data_JogNegative, Data_JogPositive;
	double   Data_JogDistance, Data_TargetVelocity;
	unsigned short	 Data_JogMode;
	
	char	 Var_Enable[34] = { "HMI_IO.XY_Mirror.CommandsX.Enable" };
	char	 Var_Stop[32] = { "HMI_IO.XY_Mirror.CommandsX.Stop" };
	char	 Var_Reset[33] = { "HMI_IO.XY_Mirror.CommandsX.Reset" };
	char	 Var_Home[32] = { "HMI_IO.XY_Mirror.CommandsX.Home" };
	char	 Var_JogDistance[39]= { "HMI_IO.XY_Mirror.CommandsX.JogDistance" };
	char	 Var_JogPositive[39]= { "HMI_IO.XY_Mirror.CommandsX.JogPositive" };
	char	 Var_JogNegative[39]= { "HMI_IO.XY_Mirror.CommandsX.JogNegative" };
	char	 Var_JogMode[35] = { "HMI_IO.XY_Mirror.CommandsX.JogMode" };
	char	 Var_TargetVelocity[42] = { "HMI_IO.XY_Mirror.CommandsX.TargetVelocity" };

	char	 Var_Enabled[39] = { "HMI_IO.XY_Mirror.StatusX.Enabled" };
	char	 Var_Ready[31] = { "HMI_IO.XY_Mirror.StatusX.Ready" };
	char	 Var_Homed[31] = { "HMI_IO.XY_Mirror.StatusX.Homed" };
	char	 Var_InPosition[36] = { "HMI_IO.XY_Mirror.StatusX.InPosition" };
	char	 Var_Moving[32] = { "HMI_IO.XY_Mirror.StatusX.Moving" };
	char	 Axis;
	};

#endif XY_MIRROR_H