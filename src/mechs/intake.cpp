#include "intake.hpp"

Intake::Intake(pros::Motor* motor)
    : motor{motor}
{
}

void Intake::move(int voltage) {
    motor->move(voltage);
}