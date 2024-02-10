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
    , enabled{false}
    , relaxed{false}
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

void Puncher::retract() {
	setVoltage(127);
	while (rotationSensor->get_angle()/100 < (TUCK_ANGLE-5) || (TUCK_ANGLE+5) < rotationSensor->get_angle()/100) {}
	brake();
}

void Puncher::move() {
    if (manual) {
        setVoltage(127);
    } else {
        moveAuto();
    }
}

void Puncher::moveAuto() {
    if (relaxed) return;
    int currentAngle = rotationSensor->get_angle() / 100;

    bool retracted = ((TUCK_ANGLE-10) < currentAngle && currentAngle < (TUCK_ANGLE+10));
    if (enabled && distanceSensor->get() < DIST_SENSOR_DIST && !loaded) {
        loaded = true;
        timeAtLoad = pros::millis();
    }

    if (loaded && (pros::millis() - timeAtLoad) > WAIT_SINCE_LOADED || !retracted) {
        brake();
        setVoltage(127);
        mode = "launching";
    }

    if (mode == "holding") {
        brake();
    } else if (mode == "retracting") {
        setVoltage(127);
        if (retracted) {
            mode = "holding";
        }
    } else if (mode == "launching") {
        loaded = false;
        setVoltage(127);
        if (currentAngle > TUCK_ANGLE + 6) {
            mode = "retracting";
        }
    }
}

void Puncher::disable(bool value) {
    enabled = !value;
}

void Puncher::relax(bool value) {
    relaxed = value;
    if (value) {
        setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    } else {
        setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    }
}

void Puncher::setBrakeMode(pros::motor_brake_mode_e brakeMode) {
    motor11->set_brake_mode(brakeMode);
    motor5_5->set_brake_mode(brakeMode);
}