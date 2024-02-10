#include "electronics.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::ADIDigitalOut wingsLeftSolenoid('A');
pros::ADIDigitalOut wingsRightSolenoid('B');

pros::ADIDigitalOut liftSolenoid('F');
pros::ADIDigitalOut kaboomerSolenoid('C');
pros::ADIDigitalIn kaboomerSwitch('Z');

pros::Motor intakeMotor(-7, pros::E_MOTOR_GEARSET_06);

pros::ADIEncoder perpendicularWheel(('H','G'), false);
pros::IMU inertialSensor(15);

pros::Rotation puncherRotationSensor(18);
pros::Distance puncherDistanceSensor(16);
pros::Motor puncherMotor11(-19, pros::E_MOTOR_GEARSET_36);
pros::Motor puncherMotor5_5(20, pros::E_MOTOR_GEARSET_36);

pros::MotorGroup leftDT({-3,-5,-6});
pros::MotorGroup rightDT({1, 2, 4});

Drivetrain drivetrain(&leftDT, &rightDT);
Intake intake(&intakeMotor);
Puncher puncher(&puncherMotor11, &puncherMotor5_5, &puncherRotationSensor, &puncherDistanceSensor);
Wings wings(&wingsLeftSolenoid, &wingsRightSolenoid);
Lift lift(&liftSolenoid, &puncher);
Hang hang(&kaboomerSolenoid, &lift, &puncher);