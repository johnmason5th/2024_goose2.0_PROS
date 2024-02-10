#include "hang.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

Hang::Hang(pros::ADIDigitalOut* solenoid, Lift* lift, Puncher* puncher)
    : solenoid{solenoid}
    , lift{lift}
    , puncher{puncher}
    , enabled{false}
{
}

void Hang::toggle() {
    enabled = !enabled;
    solenoid->set_value(enabled);
    lift->disable(enabled);
    lift->setExtended(false);

    puncher->disable(true);
    puncher->relax(true);
}