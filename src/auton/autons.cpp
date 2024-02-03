#include "autons.hpp"

void waitForInput() {
	while (true) {
		if (controller.get_digital(DIGITAL_A)) {
			return;
		}
	}
}

/**
 * Grab center triball
 * Remove mlz triball
 * score ally triball
 * dump all 3 (or 2 if hang is off limits) triballs on other side of hang
 * make it optional that we touch hang or not
*/
// Starts at angle of -20 relative to field
void nearAuton() {
	// Shoot ally triball towards goal
	wingsLeftSolenoid.set_value(true);
	pros::delay(250);
	wingsLeftSolenoid.set_value(false);

	// Grab Triball
	intakeMotor = 127;
	moveRelative(2, 1300);

	// Score ally triball
	moveRelative(-1.9, 1400);
	turnAbsolute(-157+20, 1000);
	moveRelative(-1.3, 1200);

	// Remove MLZ triball
	turnAbsolute(177+20, 650);
	moveRelative(0.45, 700);
	turnAbsolute(-120+20, 500);
	wingsRightSolenoid.set_value(true);
	moveRelative(0.6, 800);
	turnAbsolute(-105+20, 600);

	// Push triballs across hang
	intakeMotor = -127;
	moveRelative(1, 900);
	wingsRightSolenoid.set_value(false);
	turnAbsolute(-80+20, 600);
	wingsRightSolenoid.set_value(true);
	moveRelative(0.72, 1000);
	pros::delay(500);
	wingsRightSolenoid.set_value(false);
	intakeMotor = 0;
}

// -35
void farAuton() {
	// Grab center barrier triball
	intakeMotor = 127;
	moveRelative(2.52, 1400);

	// Shove triballs into goal
	turnAbsolute(-91-35, 800);
	intakeMotor = 0;
	wingsLeftSolenoid.set_value(true);
	wingsRightSolenoid.set_value(true);
	moveRelative(1.6, 1000);
	wingsLeftSolenoid.set_value(false);
	wingsRightSolenoid.set_value(false);
	moveRelative(-0.50, 600);
	// Grab third triball
	turnAbsolute(122-35, 700);
	intakeMotor = 127;
	moveRelative(1.08, 800);
	// Shove Triballs
	turnAbsolute(230-35, 600);
	moveRelative(1.81, 1500);
	turnAbsolute(-45-35, 500);
	intakeMotor = -127;
	wingsRightSolenoid.set_value(true);
	moveRelative(0.5, 700);
	turnRelative(180, 900);
	turnAbsolute(135-35, 700);
	wingsRightSolenoid.set_value(false);
	intakeMotor = 0;
	moveRelative(-1, 700);
	moveRelative(0.5, 700);
	moveRelative(-1, 700);
	moveRelative(0.5, 700);
}

void pushAuton() {
	leftDT = -100;
	rightDT = -100;
	pros::delay(1000);
	leftDT = 100;
	rightDT = 100;
	pros::delay(500);
	leftDT = 0;
	rightDT = 0;
}
/*
Prgm Skills Process:
- Scoot to touch MLZ
- launch for enough time to get all triballs over
- Go and push triballs into goal
*/
void prgmSkills() {
	puncherMotor11.set_brake_mode(MOTOR_BRAKE_HOLD);
	puncherMotor5_5.set_brake_mode(MOTOR_BRAKE_HOLD);
	// Set up for launching
	moveRelative(-0.25, 500);
	turnAbsolute(65, 800);
	moveRelative(-0.1, 500);
	liftSolenoid.set_value(true);
	int puncherStart = pros::millis();
	while ((puncherStart + 35000) < pros::millis()) {
		puncherWithRot();
	}	
	liftSolenoid.set_value(false);

	// Launch Triballs
	while (puncherRotationSensor.get_angle()/100 < (70-5) || (70+5) < puncherRotationSensor.get_angle()/100) {}
	puncherMotorsBrake();

	// Move to opposite side
	turnAbsolute(0, 1500);
	moveRelative(0.5, 800);
	turnAbsolute(45, 1000);
	moveRelative(3.2, 2000);

	// Shove first face of goal
	turnAbsolute(-15, 2400);
	moveRelative(2.4, 1500);
	turnAbsolute(-135, 1000);
	// wingsSolenoid.set_value(true);
	
	moveRelative(2, 1500);
	// wingsSolenoid.set_value(false);

	// Shove second face of goal
	moveRelative(-1.4, 1000);
	turnAbsolute(-45, 2000);
	moveRelative(0.5, 1000);
	turnAbsolute(-135, 1000);

	// wingsSolenoid.set_value(true);
	moveRelative(2, 2000);
	// wingsSolenoid.set_value(false);

	moveRelative(-1.4, 1500);
}
