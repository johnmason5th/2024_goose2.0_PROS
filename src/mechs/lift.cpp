#include "lift.hpp"

Lift::Lift(pros::ADIDigitalOut* solenoid, Puncher* puncher)
    : solenoid{solenoid}
    , puncher{puncher}
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
    puncher->disable(!value);
}

void Lift::disable(bool value) {
    enabled = !value;
}