#include "stdafx.h"
#include "XY_Mirror.h"
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsDef.h"
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsAPI.h"

using namespace std;

XYMirror::XYMirror(char Axis)
{
	
	pAddr = &Addr;
	AdsPortOpen();
	AdsGetLocalAddress(pAddr);
	pAddr->port = 851;
	
	switch (Axis) 
	{
	case 'y': // Y Axis
		Var_Enable[25] = Var_Stop[25] = Var_Reset[25] = Var_Home[25] = Var_JogDistance[25] = Var_JogPositive[25] =
		Var_JogNegative[25] = Var_JogMode[25] = Var_Enabled[23] = Var_Ready[23] = Var_Homed[23] = Var_InPosition[23] = Var_Moving[23] = 'Y';
		break;
	case 'x':  // X Axis
		Var_Enable[25] = Var_Stop[25] = Var_Reset[25] = Var_Home[25] = Var_JogDistance[25] = Var_JogPositive[25] =
		Var_JogNegative[25] = Var_JogMode[25] = Var_Enabled[23] = Var_Ready[23] = Var_Homed[23] = Var_InPosition[23] = Var_Moving[23] = 'X';
		break;
		default:
			cout << "Error. Choose x- or y- axis for XY mirror controlling";
	}
}

XYMirror::~XYMirror()
{
}

void XYMirror::Reset()
{	
		Data_Reset = true;

		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
}

void XYMirror::Ready()
{
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Enable), &Hdl_Enable, sizeof(Var_Enable), &Var_Enable);
	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
	do
	{

		do {
			long Err1 = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Enabled), &Hdl_Enabled, sizeof(Var_Enabled), &Var_Enabled);
			long Err2= AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enabled, sizeof(Data_Enabled), &Data_Enabled);
			std::cout << Err1 << Err2;
			Data_Enable = true;

			long Err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
			std::cout << Err << std::endl;
			Sleep(1000);

			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Ready), &Hdl_Ready, sizeof(Var_Ready), &Var_Ready);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Ready, sizeof(Data_Ready), &Data_Ready);

			if (Data_Ready == false)
			{
				Data_Reset = true;
				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
				Sleep(1000);
			}

			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);

		} while (Data_Enabled == false);

	} while (Data_Ready == false);
}

bool XYMirror::InPosition()
{
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_InPosition), &Hdl_InPosition, sizeof(Var_InPosition), &Var_InPosition);
	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_InPosition, sizeof(Data_InPosition), &Data_InPosition);
	return Data_InPosition;
}

void XYMirror::JogMode()
{
	long hh=AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_JogMode), &Hdl_JogMode, sizeof(Var_JogMode), &Var_JogMode);
	long hhhh= AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_JogMode, sizeof(Data_JogMode), &Data_JogMode);
	std::cout << "JodMode " << Data_JogMode;
	std::cout << "step" << Data_JogMode;
	Data_JogMode = 0; //0:= step, 1:=Continuos
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_JogMode), &Hdl_JogMode, sizeof(Var_JogMode), &Var_JogMode);
	long Err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_JogMode, sizeof(Data_JogMode), &Data_JogMode);
}

void XYMirror::Distance(double dis)
{	Data_TargetVelocity = 0.1;
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_TargetVelocity), &Hdl_TargetVelocity, sizeof(Var_TargetVelocity), &Var_TargetVelocity);
	
	long Ttt = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_TargetVelocity, sizeof(Data_TargetVelocity), &Data_TargetVelocity);
	Data_JogDistance = dis;
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_JogDistance), &Hdl_JogDistance, sizeof(Var_JogDistance), &Var_JogDistance);
	
long hhh= 	AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_JogDistance, sizeof(Data_JogDistance), &Data_JogDistance);
}

void XYMirror::JogNegative()
{
	Data_JogNegative = true;
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_JogNegative), &Hdl_JogNegative, sizeof(Var_JogNegative), &Var_JogNegative);
	AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_JogNegative, sizeof(Data_JogNegative), &Data_JogNegative);
}

void XYMirror::JogPositive()
{
	Data_JogPositive = true;
	long fff = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_JogPositive), &Hdl_JogPositive, sizeof(Var_JogPositive), &Var_JogPositive);
	long err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_JogPositive, sizeof(Data_JogPositive), &Data_JogPositive);
}