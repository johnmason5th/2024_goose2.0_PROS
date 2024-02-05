#include "electronics.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

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

pros::MotorGroup leftDT({-3,-5,-6});
pros::MotorGroup rightDT({1, 2, 4});
