#include "main.h"

PID::PID(double kp, double ki, double kd, double minError) :
	kp(kp),
	ki(ki),
	kd(kd),
	minError(minError)
{};

double PID::compute(double targetValue, double sensorValue) {
	error = targetValue - sensorValue;

	double proportional = kp * error;

	integral *= 0.95; // to prevent windup
	integral += ki * (error);

	double derivative = kd * (error - previousError);

	double output = proportional + integral + derivative;

	previousError = error;

	return output;
};

bool PID::settled() {
	// Measures if robot is stuck, stopped moving. Certain stuck time tells it is settled
	if (fabs(error - previousError) < (minError * 0.01)) {
		timeout += 10;
	} else {
		timeout = 0;
	}
	if ((fabs(error) < minError) /* && (fabs(error - previousError) < minError * 0.2) || timeout > 1400 */) {
		timeout = 0;
		return true;
	}
	return false;
}