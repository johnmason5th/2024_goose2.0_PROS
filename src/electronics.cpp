#include "electronics.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::ADIDigitalOut horizontalWingsSolenoid('A');
pros::ADIDigitalOut verticalWingsSolenoid('B');

pros::ADIDigitalOut liftSolenoid('F');
pros::ADIDigitalOut hangSolenoid('C');

pros::Motor intakeMotor(-7, pros::E_MOTOR_GEARSET_06);

pros::ADIEncoder perpendicularWheel(('H','G'), false);
pros::IMU inertialSensor(21);

pros::Rotation puncherRotationSensor(18);
pros::Distance puncherDistanceSensor(16);
pros::Motor puncherMotor11(-19, pros::E_MOTOR_GEARSET_36);
pros::Motor puncherMotor5_5(20, pros::E_MOTOR_GEARSET_36);

pros::MotorGroup leftDT({-1,-2,-3});
pros::MotorGroup rightDT({8, 9, 10});

Drivetrain drivetrain(&leftDT, &rightDT);
Intake intake(&intakeMotor);
Puncher puncher(&puncherMotor11, &puncherMotor5_5, &puncherRotationSensor, &puncherDistanceSensor);
Wings horizontalWings(&horizontalWingsSolenoid);
Wings verticalWings(&verticalWingsSolenoid);
Lift lift(&liftSolenoid, &puncher);
Hang hang(&hangSolenoid, &lift, &puncher);