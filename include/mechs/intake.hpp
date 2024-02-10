#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "pros/motors.hpp"

class Intake {
    private:
        pros::Motor* motor;
    public:
        Intake(pros::Motor* motor);
        void move(int voltage);
};

#endif