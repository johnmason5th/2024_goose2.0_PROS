#include "intake.hpp"

Intake::Intake(pros::Motor* motor)
    : motor{motor}
{
}

void Intake::spin(int voltage) {
    motor->move(voltage);
}