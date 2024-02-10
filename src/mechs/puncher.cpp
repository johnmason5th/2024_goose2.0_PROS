#include "puncher.hpp"

Puncher::Puncher(pros::Motor* motor11, pros::Motor* motor5_5, pros::Rotation* rotationSensor, pros::Distance* distanceSensor)
    : motor11{motor11}
    , motor5_5{motor5_5}
    , rotationSensor{rotationSensor}
    , distanceSensor{distanceSensor}
    , retracted{true}
    , loaded{false}
    , tuckAngle{40}
    , DIST_SENSOR_DIST{30}
    , WAIT_SINCE_LOADED{0}
    , timeAtLoad{0}
    , mode{"retracting"}
    , manual{false}
    , enabled{true}
{
}

void Puncher::brakeMotors() {
    motor11->brake();
    motor5_5->brake();
}

void Puncher::setVoltage(int volt) {
    motor11->move(volt);
    motor5_5->move(volt);
}

void Puncher::toggleManual() {
    manual = !manual;
}

void Puncher::move() {
    if (manual) {
        setVoltage(127);
    } else {
        moveAuto();
    }
}

void Puncher::moveAuto() {
    if (!enabled) return;
    int currentAngle = rotationSensor->get_angle() / 100;

    retracted = ((tuckAngle-10) < currentAngle && currentAngle < (tuckAngle+10));
    if (distanceSensor->get() < DIST_SENSOR_DIST && !loaded) {
        loaded = true;
        timeAtLoad = pros::millis();
    }

    if ((loaded && (pros::millis() - timeAtLoad) > WAIT_SINCE_LOADED) || !retracted) {
        mode = "launching";
    }

    if (mode == "holding") {
        brakeMotors();
    } else if (mode == "retracting") {
        setVoltage(127);
        if (retracted) {
            mode = "holding";
        }
    } else if (mode == "launching") {
        loaded = false;
        setVoltage(127);
        if (currentAngle > tuckAngle + 6) {
            mode = "retracting";
        }
    }
}

void Puncher::disable() {

}

void Puncher::setBrakeMode(pros::motor_brake_mode_e brakeMode) {
    motor11->set_brake_mode(brakeMode);
    motor5_5->set_brake_mode(brakeMode);
}