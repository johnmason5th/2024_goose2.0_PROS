#ifndef ELECTRONICS_HPP
#define ELECTRONICS_HPP

#include "main.h"

extern pros::Controller controller;

extern pros::ADIDigitalOut wingsLeftSolenoid;
extern pros::ADIDigitalOut wingsRightSolenoid;
extern pros::ADIDigitalIn hangSwitch;

extern pros::Motor intakeMotor;

extern pros::Rotation puncherRotationSensor;
extern pros::Distance puncherDistanceSensor;
extern pros::Motor puncherMotor11;
extern pros::Motor puncherMotor5_5;

extern pros::IMU inertialSensor;
extern pros::Motor left1;
extern pros::Motor left2;
extern pros::Motor left3;
extern pros::Motor right1;
extern pros::Motor right2;
extern pros::Motor right3;
extern bool left_3Hang;
extern bool right_3Hang;


extern pros::ADIDigitalOut liftSolenoid;
extern pros::ADIDigitalOut hangSolenoid;


extern pros::ADIEncoder perpTrackingWheel;

#endif