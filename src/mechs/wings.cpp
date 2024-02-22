#include "wings.hpp"

Wings::Wings(pros::ADIDigitalOut* solenoid)
    : solenoid{solenoid}
    , extended{false}
{
}

void Wings::toggle() {
    extended = !extended;
    solenoid->set_value(extended);
}

void Wings::extend(bool value) {
    solenoid->set_value(value);
}
