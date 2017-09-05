#include "Motor.h"
#include <string> 
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> 
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsDef.h"
#include "C:/TwinCAT/AdsApi/TcAdsDll/Include/TcAdsAPI.h"

using namespace std;

Motor::Motor(int Index) //hier erfolgt auch Änderung von working mode
{
		// muss man eigentlich nicht bei jedem motor nochmal machen?
	
	pAddr = &Addr;
	long nPort = AdsPortOpen();
	long GlobalError = AdsGetLocalAddress(pAddr);
	pAddr->port = 851;
	
	// anders initialisieren?
	
	/*
	 Var_CurPosition[39] = {"HMI_IO.Values[0].Position.Cur_Position"};
	 Var_SetPosition[39] = { "HMI_IO.Values[0].Position.Set_Position" };
	 Var_GetAxisMode[30] = { "HMI_IO.Befehle[0].GetAxisMode" };
	 Var_SetAxisMode[30] = { "HMI_IO.Befehle[0].SetAxisMode" };
	 Var_Reset[24] = { "HMI_IO.Befehle[0].Reset" };
	 Var_Error[24] = { "HMI_IO.Befehle[0].Error" };
	 Var_Enable[25] = { "HMI_IO.Befehle[0].Enable" };
	 Var_Disable[26] = { "HMI_IO.Befehle[0].Disable" };
	 Var_Position[27] = { "HMI_IO.Befehle[0].Position" };
	 Var_Velocity[27] = { "HMI_IO.Befehle[0].Velocity" };
	 Var_Move_Start[29] = { "HMI_IO.Befehle[0].Move_Start" };
	 Var_Move_Stop[28] = { "HMI_IO.Befehle[0].Move_Stop" };
	 Var_MovetoReference[34] = { "HMI_IO.Befehle[0].MovetoReference" };
	 Var_is_Homed[27] = { "HMI_IO.Befehle[0].is_Homed" };
	 Var_is_Enable[28] = { "HMI_IO.Befehle[0].is_Enable" };
	 Var_in_Position[30] = { "HMI_IO.Befehle[0].in_Position" };
	 Var_is_Moving[28] = { "HMI_IO.Befehle[0].is_Moving" };
	 Var_GetWorkingMode[33] = { "HMI_IO.Befehle[0].GetWorkingMode" };
	 Var_SetWorkingMode[33] = { "HMI_IO.Befehle[0].SetWorkingMode" };
	 */
	//Index.  to change a variablename
	switch (Index)
	{
		//Keilplattenmotor
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

		//Spindel modus wechseln im Hohlwellenmotor

		//Get  Axismode
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_GetAxisMode), &Hdl_GetAxisMode, sizeof(Var_GetAxisMode), &Var_GetAxisMode);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetAxisMode, sizeof(Data_GetAxisMode), &Data_GetAxisMode);
		
		while (Data_GetAxisMode != 1)
		{
			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_SetAxisMode), &Hdl_SetAxisMode, sizeof(Var_SetAxisMode), &Var_SetAxisMode);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_SetAxisMode, sizeof(Data_SetAxisMode), &Data_SetAxisMode);

			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Enable), &Hdl_Enable, sizeof(Var_Enable), &Var_Enable);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);

			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
			//Get  Axismode
			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_GetAxisMode), &Hdl_GetAxisMode, sizeof(Var_GetAxisMode), &Var_GetAxisMode);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetAxisMode, sizeof(Data_GetAxisMode), &Data_GetAxisMode);

			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Disable), &Hdl_Disable, sizeof(Var_Disable), &Var_Disable);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Disable, sizeof(Data_Disable), &Data_Disable);

			if (Data_GetAxisMode != 0)
			{
				Data_Disable = true;
				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Disable, sizeof(Data_Disable), &Data_Disable);
				Sleep(1000);
			}

			Data_SetAxisMode = 1;
			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_SetAxisMode, sizeof(Data_SetAxisMode), &Data_SetAxisMode);
			Sleep(1000);

			while (Data_is_Enable == false) {
				Data_Enable = true;
				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Enable, sizeof(Data_Enable), &Data_Enable);
				Sleep(1000);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);
			}


			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);

			while (Data_Error == false)
			{
				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
				Data_Reset = true;
				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
				Sleep(1000);
				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);

			}
			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_GetAxisMode), &Hdl_GetAxisMode, sizeof(Var_GetAxisMode), &Var_GetAxisMode);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetAxisMode, sizeof(Data_GetAxisMode), &Data_GetAxisMode);
		} 

		break;
	default:
		Var_Error[15] = Var_Reset[15] = Var_CurPosition[14] = Var_GetWorkingMode[14] = Var_SetWorkingMode[14] =
			Var_Enable[15] = Var_Disable[15] = Var_Position[15] = Var_Velocity[15]
			= Var_Move_Start[15] = Var_Move_Stop[15] = Var_MovetoReference[15] = Var_SetAxisMode[15]
			= Var_is_Enable[15] = Var_is_Homed[15] = Var_in_Position[15]
			= Var_is_Moving[15] = Var_GetAxisMode[15] = '0';
	}

	// WorkingMode
	// 0 - Jog
	// 1 - Manuell
	// 2 - Automatisch

	//  Disable -> GetAWorkingMode -> SetWorkingMode -> Enable -> Error -> Reset
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

	cout <<"Initialisation was successful"<< endl;
}

Motor::~Motor()
{
}

//in_Position beinhaltet State Machine
void Motor::GoToPosition(double velocity, double position)
{
	
	enum States { Idle = 0, Moving, in_Position, Error, Enable, Disable, Home };
	States Zustand = Idle;

	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_CurPosition), &Hdl_CurPosition, sizeof(Var_CurPosition), &Var_CurPosition);
	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_CurPosition, sizeof(Data_CurPosition), &Data_CurPosition);

	while (position != Data_CurPosition)
	{
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);

		while (Zustand != Home)
		{
			switch (Zustand) {

			case Idle:
				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);

				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);

				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);

				//Motor stoppen
				if (Data_is_Moving == true)
				{
					Data_Move_Stop = true;
					AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Stop), &Hdl_Move_Stop, sizeof(Var_Move_Stop), &Var_Move_Stop);
					AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Stop, sizeof(Data_Move_Stop), &Data_Move_Stop);

					Sleep(5000);
				}

				if (Data_is_Enable == true) { Zustand = Enable; }
				else if (Data_is_Enable == false) { Zustand = Disable; }
				else { Zustand = Error; }
				break;

			case Error:
				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
				if (Data_Error == false)
				{
					Data_Reset = true;

					AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
					AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
					Zustand = Idle;
				}
				break;

			case Enable:
				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);

				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_MovetoReference), &Hdl_MovetoReference, sizeof(Var_MovetoReference), &Var_MovetoReference);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_MovetoReference, sizeof(Data_MovetoReference), &Data_MovetoReference);

				//MovetoReference 
				Data_MovetoReference = true;

				AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_MovetoReference, sizeof(Data_MovetoReference), &Data_MovetoReference);
				Sleep(5000);

				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Homed), &Hdl_is_Homed, sizeof(Var_is_Homed), &Var_is_Homed);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Homed, sizeof(Data_is_Homed), &Data_is_Homed);

				if (Data_is_Homed == true) { Zustand = Home; }
				else { Zustand = Enable; }
				break;

			case Home:
				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);

				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);

				if (Data_is_Moving) { Zustand = Moving; }
				else { Zustand = Home; }
				break;

			case Moving:
				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Homed), &Hdl_is_Homed, sizeof(Var_is_Homed), &Var_is_Homed);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Homed, sizeof(Data_is_Homed), &Data_is_Homed);

				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);

				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);

				if (Data_is_Moving == true)
				{
					Data_Move_Stop = true;
					AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Stop), &Hdl_Move_Stop, sizeof(Var_Move_Stop), &Var_Move_Stop);
					AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Stop, sizeof(Data_Move_Stop), &Data_Move_Stop);

					Sleep(5000);
				}
				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);

				if (Data_is_Moving == true) { Zustand = Moving; }
				else if (Data_is_Homed) { Zustand = Home; }
				else if (Data_is_Enable == true) { Zustand = Enable; }
				break;

			case Disable:
				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);

				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Enable), &Hdl_is_Enable, sizeof(Var_is_Enable), &Var_is_Enable);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Enable, sizeof(Data_is_Enable), &Data_is_Enable);

				Data_Enable = true;

				AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
				AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);

				if (Data_is_Enable == true) { Zustand = Enable; }
				else if (Data_Error == true) { Zustand = Error; }
				else { Zustand = Disable; }
				break;

			default:
			{Zustand = Idle; }
			}
		}

	//velocity einstellen
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Velocity), &Hdl_Velocity, sizeof(Var_Velocity), &Var_Velocity);
	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Velocity, sizeof(Data_Velocity), &Data_Velocity);
	Data_Velocity = velocity;
	AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Velocity, sizeof(Data_Velocity), &Data_Velocity);
	Sleep(1000);

	//position einstellen
	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Position), &Hdl_Position, sizeof(Var_Position), &Var_Position);
	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Position, sizeof(Data_Position), &Data_Position);
	Data_Position = position;
	AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Position, sizeof(Data_Position), &Data_Position);
	Sleep(1000);

	do
	{
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Start), &Hdl_Move_Start, sizeof(Var_Move_Start), &Var_Move_Start);
		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Start, sizeof(Data_Move_Start), &Data_Move_Start);
		Data_Move_Start = true;
		AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Start, sizeof(Data_Move_Start), &Data_Move_Start);

		Sleep(10000);

		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_GetAxisMode, sizeof(Data_GetAxisMode), &Data_GetAxisMode);

		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_in_Position), &Hdl_in_Position, sizeof(Var_in_Position), &Var_in_Position);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_in_Position, sizeof(Data_in_Position), &Data_in_Position);
	} while (Data_in_Position == false);

	AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_CurPosition), &Hdl_CurPosition, sizeof(Var_CurPosition), &Var_CurPosition);
	AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_CurPosition, sizeof(Data_CurPosition), &Data_CurPosition);
}

	// Release the handle of the PLC-variable
	long nErr_Enable = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(Hdl_Enable), &Hdl_Enable);
	if (nErr_Enable) cerr << "Error: AdsSyncWriteReq: Enable " << nErr_Enable << '\n';
	if (nErr_Enable) cerr << "Error: AdsPortClose: Enable " << nErr_Enable << '\n';
	cout << " Hollowshaftmotor is in Position " << position << endl;
}

void Motor::Reset()
	{
		//1. Schleife error -> reset
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);

		do
		{
			Data_Reset = true;

			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Reset), &Hdl_Reset, sizeof(Var_Reset), &Var_Reset);
			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Reset, sizeof(Data_Reset), &Data_Reset);
			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Error), &Hdl_Error, sizeof(Var_Error), &Var_Error);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Error, sizeof(Data_Error), &Data_Error);
		} while (Data_Error == false);
	}

void Motor::MovingCheck()
	{
		//2. Schleife is_Moving -> Moving_Stop
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Stop), &Hdl_Move_Stop, sizeof(Var_Move_Stop), &Var_Move_Stop);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Stop, sizeof(Data_Move_Stop), &Data_Move_Stop);

		do
		{
			Data_Move_Stop = true;

			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_Move_Stop), &Hdl_Move_Stop, sizeof(Var_Move_Stop), &Var_Move_Stop);
			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_Move_Stop, sizeof(Data_Move_Stop), &Data_Move_Stop);

			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Moving), &Hdl_is_Moving, sizeof(Var_is_Moving), &Var_is_Moving);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Moving, sizeof(Data_is_Moving), &Data_is_Moving);
		} while (Data_is_Moving == true);

	}

void Motor::Homed()
	{
		//4. Schleife isHomed -> Reference
		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_is_Homed), &Hdl_is_Homed, sizeof(Var_is_Homed), &Var_is_Homed);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_is_Homed, sizeof(Data_is_Homed), &Data_is_Homed);

		AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_CurPosition), &Hdl_CurPosition, sizeof(Var_CurPosition), &Var_CurPosition);
		AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_CurPosition, sizeof(Data_CurPosition), &Data_CurPosition);


		if ((!Data_is_Homed) || (Data_CurPosition < 360))
		{
			AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(Hdl_MovetoReference), &Hdl_MovetoReference, sizeof(Var_MovetoReference), &Var_MovetoReference);
			AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_MovetoReference, sizeof(Data_MovetoReference), &Data_MovetoReference);

			Data_MovetoReference = true;
			AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, Hdl_MovetoReference, sizeof(Data_MovetoReference), &Data_MovetoReference);
			Sleep(1000);
		}
	}

void Motor::PortClose()
	{
		// Close the communication port
		AdsPortClose();
	}