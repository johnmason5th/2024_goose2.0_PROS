#include "mechs.hpp"

// Drivetrain Helper Functions

void setDrivetrainBrakeMode(pros::motor_brake_mode_e brakeMode) {
    leftDT.set_brake_modes(brakeMode);
	rightDT.set_brake_modes(brakeMode);
}

int leftDTTarget {0};
int rightDTTarget{0};
void drivetrain() {
    // Get joystick values and assign to variables
    int speed = exponentialJoystick(controller.get_analog(ANALOG_LEFT_Y));
    int turn = exponentialJoystick(controller.get_analog(ANALOG_RIGHT_X)) * 0.7;
    
    // Deadzone of -5 to 5 for each joystick
    if(abs(speed) < 5) {
        speed = 0;
    }
    if(abs(turn) < 5) {
        turn = 0;
    }

    // Drivetrain Control
    leftDTTarget = speed+turn;
    rightDTTarget = speed-turn;

	leftDT = leftDTTarget;
	rightDT = rightDTTarget;
}

void intake() {
    if (controller.get_digital(DIGITAL_L1)) {
        intakeMotor = 127;
    } else if (controller.get_digital(DIGITAL_L2)) {
        intakeMotor = -127;
    } else {
        intakeMotor = 0;
    }
}

bool puncherEnabled = true;
bool liftEnabled = false;

bool retracted = true;
bool loaded = false;
int tuckAngle = 50;
const int DIST_SENSOR_DIST = 30;
const int WAIT_SINCE_LOADED = 0;
int timeAtLoad = 0;
std::string mode = "retracting";
void puncherWithRot() {
    if (!puncherEnabled) return;
    int currentAngle = puncherRotationSensor.get_angle() / 100;

    retracted = ((tuckAngle-5) < currentAngle && currentAngle < (tuckAngle+5));
    if (liftEnabled && puncherDistanceSensor.get() < DIST_SENSOR_DIST && !loaded) {
        loaded = true;
        timeAtLoad = pros::millis();
    }

    if (loaded && (pros::millis() - timeAtLoad) > WAIT_SINCE_LOADED) {
        mode = "launching";
    }

    if (mode == "holding") {
        puncherMotorsBrake();
    } else if (mode == "retracting") {
        puncherMotorsVolt(127);
        if (retracted) {
            mode = "holding";
        }
    } else if (mode == "launching") {
        loaded = false;
        puncherMotorsVolt(127);
        if (currentAngle > tuckAngle + 6) {
            mode = "retracting";
        }
    }
}
bool matchloading = false;
void puncherDumb() {
    if (controller.get_digital_new_press(DIGITAL_Y)) {
        matchloading = !matchloading;
    }
    if (matchloading) {
        puncherMotorsVolt(127);
    } else {
        puncherMotorsBrake();
    }
}

void puncherMotorsBrake() {
    puncherMotor11.brake();
    puncherMotor5_5.brake();
}
void puncherMotorsVolt(int volt) {
    puncherMotor11 = volt;
    puncherMotor5_5 = volt;
}

bool wingsOut = false;
void wings() {
    if (controller.get_digital_new_press(DIGITAL_R2)) {
        wingsOut = !wingsOut;
        wingsLeftSolenoid.set_value(wingsOut);
        wingsRightSolenoid.set_value(wingsOut);
    }
}

bool hangEnabled = false;
void lift() {
    if (controller.get_digital_new_press(DIGITAL_R1) && !hangEnabled) {
        liftEnabled = !liftEnabled;
        liftSolenoid.set_value(liftEnabled);
    }
}

void hang() {
    if (controller.get_digital_new_press(DIGITAL_UP)) {
        hangEnabled = true;
        hangSolenoid.set_value(true);
        liftSolenoid.set_value(false);

        puncherEnabled = false;
        puncherMotor11.set_brake_mode(MOTOR_BRAKE_COAST);
        puncherMotor5_5.set_brake_mode(MOTOR_BRAKE_COAST);
    }
}
