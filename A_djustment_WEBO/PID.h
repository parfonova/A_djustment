#pragma once

#ifndef _PID_H_
#define _PID_H_

class PIDImpl;
class PID
{
public:
	// Kp -  proportional gain
	// Ki -  Integral gain
	// Kd -  derivative gain
	// dt -  loop interval time
	// max - maximum value of manipulated variable
	// min - minimum value of manipulated variable
	PID(double dt, double max, double min, double Kp, double Kd, double Ki);

	// Returns the manipulated variable given a soll_position and current process value
	double calculate(double soll_position, double ist_position);
	~PID();

private:
	PIDImpl *pimpl;
};

#endif