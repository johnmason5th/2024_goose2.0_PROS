#ifndef PID_HPP
#define PID_HPP

#include "main.h"

class PID {
private:
	double error = 0;
    double targetValue = 0;
	double kp = 0;
	double ki = 0;
	double kd = 0;
	double integral = 0;
	double integralLimit = 10;
	double previousError = 0;
	double output = 0;
	double minError = 0.01;
	double timeout = 0;

public:
    PID(double kp, double ki, double kd, double minError);
	
	/**
	 * @param targetValue target value for sensor
	 * @param sensorValue input from sensor
	*/
    double compute(double targetValue, double currentValue);
    bool settled();
};

#endif