#include "drivetrain.hpp"

Drivetrain::Drivetrain(pros::MotorGroup* leftMotors, pros::MotorGroup* rightMotors)
    : leftMotors{leftMotors}
    , rightMotors{rightMotors}
{
}

void Drivetrain::arcade(int speed, int turn) {
    // Deadzone of -5 to 5 for each joystick
    if(abs(speed) < 5) {
        speed = 0;
    }
    if(abs(turn) < 5) {
        turn = 0;
    }

    // Drivetrain Control
    leftMotors->move(speed+turn);
    rightMotors->move(speed-turn);
}

void Drivetrain::setBrakeMode(pros::motor_brake_mode_e brakeMode) {
    leftMotors->set_brake_modes(brakeMode);
	rightMotors->set_brake_modes(brakeMode);
}