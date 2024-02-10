#ifndef ELECTRONICS_HPP
#define ELECTRONICS_HPP

#include "main.h"

extern pros::Controller controller;

extern pros::ADIDigitalOut wingsLeftSolenoid;
extern pros::ADIDigitalOut wingsRightSolenoid;

extern pros::ADIDigitalOut liftSolenoid;
extern pros::ADIDigitalOut kaboomerSolenoid;
extern pros::ADIDigitalIn kaboomerSwitch;

extern pros::Motor intakeMotor;

extern pros::ADIEncoder perpendicularWheel;
extern pros::IMU inertialSensor;

extern pros::Rotation puncherRotationSensor;
extern pros::Distance puncherDistanceSensor;
extern pros::Motor puncherMotor11;
extern pros::Motor puncherMotor5_5;

extern pros::MotorGroup leftDT;
extern pros::MotorGroup rightDT;

extern Drivetrain drivetrain;
extern Intake intake;
extern Puncher puncher;
extern Wings wings;
extern Lift lift;
extern Hang hang;

#endif