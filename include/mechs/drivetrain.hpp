#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include "pros/motors.hpp"
#include "pros/misc.hpp"

class Drivetrain {
    private:
        pros::MotorGroup* leftMotors;
        pros::MotorGroup* rightMotors;
    public:
        Drivetrain(pros::MotorGroup* leftMotors, pros::MotorGroup* rightMotors);
        void arcade(int speed, int turn);
        void setBrakeMode(pros::motor_brake_mode_e brakeMode);
};

#endif