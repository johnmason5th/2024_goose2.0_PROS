#include "hang.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

Hang::Hang(pros::ADIDigitalOut* solenoid, Lift* lift, Puncher* puncher)
    : solenoid{solenoid}
    , enabled{false}
    , lift{lift}
    , puncher{puncher}
{
}

void Hang::enable(bool value) {
    if (value) {
        enabled = true;
        solenoid->set_value(true);
        lift->disable();
        lift->setExtended(false);

        puncher->disable();
        puncher->setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    }
}