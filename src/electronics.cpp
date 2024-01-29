#include "main.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

/*
A - Left wing
B - Right wing
C - Hang
F - Lift

*/ 

pros::ADIDigitalOut wingsLeftSolenoid('A');
pros::ADIDigitalOut wingsRightSolenoid('B');

pros::ADIDigitalOut liftSolenoid('F');
pros::ADIDigitalOut hangSolenoid('C');
pros::ADIDigitalIn hangSwitch('Z');

pros::Motor intakeMotor(7, pros::E_MOTOR_GEARSET_06, true);

pros::ADIEncoder perpendicularWheel(('H','G'), false);
pros::IMU inertialSensor(17);

pros::Rotation puncherRotationSensor(15);
pros::Distance puncherDistanceSensor(18);
pros::Motor puncherMotor11(20, pros::E_MOTOR_GEARSET_36, true);
pros::Motor puncherMotor5_5(16, pros::E_MOTOR_GEARSET_36, false);


pros::Motor left1(-6);
pros::Motor left2(-5);
pros::Motor left3(-3);
pros::Motor right1(1);
pros::Motor right2(2);
pros::Motor right3(4);
bool left_3Hang = false;
bool right_3Hang = false;

