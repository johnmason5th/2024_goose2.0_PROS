#include "lift.hpp"

Lift::Lift(pros::ADIDigitalOut* solenoid)
    : solenoid{solenoid}
    , extended{false}
    , enabled{true}
{
}

void Lift::toggle() {
    if (enabled) {
        extended = !extended;
        setExtended(extended);
    }
}

void Lift::setExtended(bool value) {
    extended = value;
    solenoid->set_value(extended);
}

void Lift::disable() {
    enabled = false;
}