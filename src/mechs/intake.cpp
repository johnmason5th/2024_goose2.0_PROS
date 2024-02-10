#include "intake.hpp"

Intake::Intake(pros::Motor* motor)
    : motor{motor}
{
}
void Intake::setMovement(int direction) {
    motor->move(127*direction);
}