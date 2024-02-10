#include "puncher.hpp"

Puncher::Puncher(pros::Motor* motor11, pros::Motor* motor5_5, pros::Rotation* rotationSensor, pros::Distance* distanceSensor)
    : motor11{motor11}
    , motor5_5{motor5_5}
    , rotationSensor{rotationSensor}
    , distanceSensor{distanceSensor}
    , loaded{false}
    , TUCK_ANGLE{40}
    , DIST_SENSOR_DIST{30}
    , WAIT_SINCE_LOADED{0}
    , timeAtLoad{0}
    , mode{"retracting"}
    , manual{false}
    , enabled{true}
{
}

void Puncher::brake() {
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

    bool retracted = ((TUCK_ANGLE-10) < currentAngle && currentAngle < (TUCK_ANGLE+10));
    if (distanceSensor->get() < DIST_SENSOR_DIST && !loaded) {
        loaded = true;
        timeAtLoad = pros::millis();
    } else {
        loaded = false;
    }

    if (loaded && (pros::millis() - timeAtLoad) > WAIT_SINCE_LOADED) {
        mode = "launching";
    }
    if (!retracted) {
        brake();
        setVoltage(127);
        mode = "launching";
    } else {
        brake();
    }

    if (mode == "holding") {
        brake();
    } else if (mode == "retracting") {
        setVoltage(127);
        if (retracted) {
            mode = "holding";
        }
    } else if (mode == "launching") {
        setVoltage(127);
        if (currentAngle > TUCK_ANGLE + 6) {
            mode = "retracting";
        }
    }
}

void Puncher::disable() {
    enabled = false;
}

void Puncher::setBrakeMode(pros::motor_brake_mode_e brakeMode) {
    motor11->set_brake_mode(brakeMode);
    motor5_5->set_brake_mode(brakeMode);
}