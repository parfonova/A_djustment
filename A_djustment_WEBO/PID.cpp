#ifndef _PID_SOURCE_
#define _PID_SOURCE_

#include <iostream>
#include <cmath>
#include "PID.h"



class PIDImpl
{
public:
	PIDImpl(double dt, double max, double min, double Kp, double Kd, double Ki);
	~PIDImpl();
	double calculate(double soll_position, double ist_position);

private:
	double _dt;
	double _max;
	double _min;
	double _Kp;
	double _Kd;
	double _Ki;
	double _pre_error;
	double _integral;
};


PID::PID(double dt, double max, double min, double Kp, double Kd, double Ki)
{
	pimpl = new PIDImpl(dt, max, min, Kp, Kd, Ki);
}
double PID::calculate(double soll_position, double ist_position)
{
	return pimpl->calculate(soll_position, ist_position);
}
PID::~PID()
{
	delete pimpl;
}


/**
* Implementation
*/
PIDImpl::PIDImpl(double dt, double max, double min, double Kp, double Kd, double Ki) :
	_dt(dt),
	_max(max),
	_min(min),
	_Kp(Kp),
	_Kd(Kd),
	_Ki(Ki),
	_pre_error(0),
	_integral(0)
{
}

double PIDImpl::calculate(double soll_position, double ist_position)
{

	// Calculate error in Pixels
	double error = soll_position - ist_position;
	
	// Proportional term
	double Pout = _Kp * error;

	// Integral term
	_integral += error * _dt;
	double Iout = _Ki * _integral;

	// Derivative term
	double derivative = (error - _pre_error) / _dt;
	double Dout = _Kd * derivative;

	// Calculate total output
	double output = Pout + Iout + Dout;

	// Restrict to max/min
	if (output > _max)
		output = _max;
	else if (output < _min)
		output = _min;

	// Save error to previous error
	_pre_error = error;

	return output;
}

PIDImpl::~PIDImpl()
{
}

#endif _PID_SOURCE_