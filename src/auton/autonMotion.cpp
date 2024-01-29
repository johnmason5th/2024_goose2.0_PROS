#include "main.h"
#include "auton/autonMotion.hpp"

// Helper Functions
double avgDriveEncoderValue() {
	return (left2.get_position() + right1.get_position()) / 2.0;
}

void resetDriveEncoders() {
	left2.tare_position();
	right1.tare_position();
}

int prevLeftVolt = 0;
int prevRightVolt = 0;
const int minDeltaVolt = 8;
void setDrive(int leftVoltage, int rightVoltage) {
	if (abs(leftVoltage - prevLeftVolt) > minDeltaVolt) {
		int direction = abs(leftVoltage - prevLeftVolt)/(leftVoltage - prevLeftVolt);
		leftVoltage = prevLeftVolt + (5 * direction);
	}
	prevLeftVolt = leftVoltage;

	if (abs(rightVoltage - prevRightVolt) > minDeltaVolt) {
		int direction = abs(rightVoltage - prevRightVolt)/(rightVoltage - prevRightVolt);
		rightVoltage = prevRightVolt + (5 * direction);
	}
	prevRightVolt = rightVoltage;

	left1 = leftVoltage;
	left2 = leftVoltage;
	if (!left_3Hang)
	left3 = leftVoltage;
	right1 = rightVoltage;
	right2 = rightVoltage;
	if (!right_3Hang)
	right_3 = rightVoltage;
}

bool touchHang = true;
void touchHangToggle(bool touch) {
	touchHang = touch;
}

int voltageClamp(int currentValue, int upperLowerLimit) {
	return std::min(abs(currentValue), upperLowerLimit) * abs(currentValue)/(currentValue);
}

// Movement Functions

/*
Concept:
- Use values of current bot point and target point
- Make bot turn towards target point and move
- repeat
- Ideally make bot turn least distance for heading

- Current angle vs target angle. Get least distance (<180) to turn and turn in that direction
- Probably just tell robot to turn and then move a certain distance rather than do turning and moving at same time
- Do same time code later
*/
double to_deg(double rad) {
	return rad * 180 / PI;
}
double to_rad(double deg) {
	return deg * PI / 180;
}
double reduceNegative180to180(double angle) {
	while(!(angle >= -180 && angle < 180)) {
		if( angle < -180 ) { angle += 360; }
		if(angle >= 180) { angle -= 360; }
	}
	return angle;
}
const double TILES_TO_INCHES = 23.75;
const double INCHES_TO_ENCODER_UNITS = (300.0/(3.1875*PI));
const double GEAR_RATIO = 60.0/36.0;
void moveToPoint(double targetX, double targetY, int maxMilliseconds, int voltage) {
	voltage = std::min(127, voltage);
	resetDriveEncoders();

	PID drivePID = PID(0.3, 0.0, 3, 5);
	PID turnPID = PID(2.4, 0.0, 0.5, 2);

	double leftDrivePrevSpeed = 0;
	double rightDrivePrevSpeed = 0;
		double driveError = hypot(targetX-g_robotX, targetY-g_robotY) * 24*INCHES_TO_ENCODER_UNITS;
		pros::delay(50);
		controller.print(0,0,(std::to_string(driveError)).c_str());
		double reducedTo360CurrentRobotHeading = fmod(-g_robotHeading, 360);
 		double headingError = reduceNegative180to180(to_deg(atan2(targetX-g_robotX, targetY-g_robotY)) - reducedTo360CurrentRobotHeading);
		double driveOutput = drivePID.compute(driveError, avgDriveEncoderValue());
		double headingScaleFactor = cos(to_rad(headingError));
		driveOutput *= headingScaleFactor;

		double turnOutput  = voltageClamp(turnPID.compute(headingError, g_robotHeading), voltage);
	
	int initialTime = pros::millis();
	while(!(drivePID.settled() || ((pros::millis() - initialTime) > maxMilliseconds))) {
		driveError = hypot(targetX-g_robotX, targetY-g_robotY) * 24*INCHES_TO_ENCODER_UNITS;
		pros::delay(50);
		controller.print(0,0,(std::to_string(driveError)).c_str());
		reducedTo360CurrentRobotHeading = fmod(g_robotHeading, 360);
 		headingError = reduceNegative180to180(to_deg(atan2(targetX-g_robotX, targetY-g_robotY)) - reducedTo360CurrentRobotHeading);
		driveOutput = drivePID.compute(driveError, avgDriveEncoderValue());
		headingScaleFactor = cos(to_rad(headingError));
		driveOutput *= headingScaleFactor;

		double turnOutput  = voltageClamp(turnPID.compute(headingError, g_robotHeading), voltage);

		double leftDriveVoltage = driveOutput + turnOutput;
		double rightDriveVoltage = driveOutput - turnOutput;

		setDrive(leftDriveVoltage, rightDriveVoltage);

		pros::delay(10);
	}

	left1.brake();
	left2.brake();
	if (!left_3Hang)
		left3.brake();
	right1.brake();
	right2.brake();
	if (!right_3Hang)
		right_3.brake();
}

void moveRelative(double tiles, int maxMilliseconds, int voltage) {
	voltage = std::min(127, voltage);
	resetDriveEncoders();

	double tilesToEncoderUnits = tiles * TILES_TO_INCHES * INCHES_TO_ENCODER_UNITS * GEAR_RATIO;
	double targetDistance = tilesToEncoderUnits;
	double headingInitial = g_robotHeading;

	PID drivePID = PID(0.3, 0.0, 4, 5);
	PID turnPID = PID(2.4, 0.0, 0.0, 2);

	double leftDrivePrevSpeed = 0;
	double rightDrivePrevSpeed = 0;
	
	double driveOutput = drivePID.compute(targetDistance, avgDriveEncoderValue());
	double turnOutput  = turnPID.compute(headingInitial, g_robotHeading);
	int initialTime = pros::millis();
	while(!(drivePID.settled() || ((pros::millis() - initialTime) > maxMilliseconds))) {
		driveOutput = voltageClamp(drivePID.compute(targetDistance, avgDriveEncoderValue()), voltage);
		turnOutput  = voltageClamp(turnPID.compute(headingInitial, g_robotHeading), voltage);

		double leftDriveVoltage = driveOutput + turnOutput;
		double rightDriveVoltage = driveOutput - turnOutput;

		setDrive(leftDriveVoltage, rightDriveVoltage);

		pros::delay(10);
	}
	left1.brake();
	left2.brake();
	if (!left_3Hang)
		left3.brake();
	right1.brake();
	right2.brake();
	if (!right_3Hang)
		right_3.brake();
}

void turnRelative(double degrees, int maxMilliseconds, int voltage) {
	double headingInitial = g_robotHeading;
	double targetSensorValue = headingInitial - degrees;

	PID turnPID = PID(1.8, 0.0, 20, 1);
	double turnPIDOutput = turnPID.compute(targetSensorValue, g_robotHeading);
	int initialTime = pros::millis();
	while (!(turnPID.settled() || ((pros::millis() - initialTime) > maxMilliseconds))) {
		turnPIDOutput = voltageClamp(turnPID.compute(targetSensorValue, g_robotHeading), voltage);

		double turnOutput = turnPIDOutput;

		setDrive(turnOutput, -turnOutput);
		pros::delay(10);
	}
	left1.brake();
	left2.brake();
	if (!left_3Hang)
	left3.brake();
	right1.brake();
	right2.brake();
	if(!right_3Hang)
	right_3.brake();
}

/**
 * Sets robot angle to face global heading
 * @param degrees Angle from 0 (initial angle) to 360
*/
void turnAbsolute(double degrees, int maxMilliseconds, int voltage) {
	double reducedTo360CurrentRobotHeading = fmod(-g_robotHeading, 360);
	if (reducedTo360CurrentRobotHeading < 0) {
		reducedTo360CurrentRobotHeading = 360 + reducedTo360CurrentRobotHeading;
	}
	double targetRelativeHeading = degrees - reducedTo360CurrentRobotHeading;
	if (targetRelativeHeading > 180) {
		targetRelativeHeading = 360 - targetRelativeHeading;
	} else if (targetRelativeHeading < -180) {
		targetRelativeHeading = 360 + targetRelativeHeading;
	}
	turnRelative(targetRelativeHeading, maxMilliseconds, voltage);
}
