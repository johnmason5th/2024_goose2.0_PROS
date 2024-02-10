#ifndef ELECTRONICS_HPP
#define ELECTRONICS_HPP

#include "main.h"

extern pros::Controller controller;

extern pros::ADIEncoder perpendicularWheel;
extern pros::IMU inertialSensor;

extern pros::MotorGroup leftDT;
extern pros::MotorGroup rightDT;

extern Drivetrain drivetrain;
extern Intake intake;
extern Puncher puncher;
extern Wings wings;
extern Lift lift;
extern Hang hang;

#endif