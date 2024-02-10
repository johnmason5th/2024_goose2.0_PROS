#include "wings.hpp"

Wings::Wings(pros::ADIDigitalOut* leftSolenoid, pros::ADIDigitalOut* rightSolenoid)
    : leftSolenoid{leftSolenoid}
    , rightSolenoid{rightSolenoid}
    , extended{false}
{
}
void Wings::toggle() {
    extended = !extended;
    leftSolenoid->set_value(extended);
    rightSolenoid->set_value(extended);
}