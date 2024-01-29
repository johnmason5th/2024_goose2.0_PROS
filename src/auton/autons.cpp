#include "autons.hpp"

/**
 * Grab center triball
 * Remove mlz triball
 * score ally triball
 * dump all 3 (or 2 if hang is off limits) triballs on other side of hang
 * make it optional that we touch hang or not
*/
// Starts at angle of -20 relative to field
void nearAuton() {
	// Grab Center Triball
	intakeMotor = 127;
	moveRelative(2, 1500);
	// Remove MLZ Triball
	moveRelative(-1.8, 1500);
	wingsLeftSolenoid.set_value(true);
	turnRelative(245, 1200);
	turnAbsolute(210+20, 1000);
	// Score Ally Triball
	
	// Dump Triballs

	// Optional: Touch Hang
}

// -35
void farAuton() {
	// Dump ally triball
	intakeMotor = 127;
	moveRelative(1.6, 1600);
	turnAbsolute(0-35, 1000);
	intakeMotor = -127;
	pros::delay(1000);
	// Grab center barrier triball
	turnAbsolute(35-35, 1000);
	moveRelative(0.7, 1000);

	// Shove triballs into goal
	turnAbsolute(-90-35, 1500);
	intakeMotor = 0;
	wingsLeftSolenoid.set_value(true);
	wingsRightSolenoid.set_value(true);
	moveRelative(1.58, 1000);
	wingsLeftSolenoid.set_value(false);
	wingsRightSolenoid.set_value(false);
	moveRelative(-0.50, 1000);
	// Grab third triball
	turnAbsolute(130-35, 1500);
	intakeMotor = -127;
	moveRelative(1.24, 1000);
	// Score triball
	turnAbsolute(281-35, 1300);
	intakeMotor = 0;
	moveRelative(2, 1200);
	moveRelative(-0.5, 1000);

	// Go to hang
	turnAbsolute(190-35, 1000);
	moveRelative(2, 1200);
	turnAbsolute(90-35, 1000);
	moveRelative(1.23, 1000);
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
	puncherMotorsVolt(120);
	// pros::delay(2000);
	pros::delay(35 * 1000);
	liftSolenoid.set_value(false);

	// Move to opposite side
	while (puncherRotationSensor.get_angle()/100 < (70-5) || (70+5) < puncherRotationSensor.get_angle()/100) {}
	puncherMotorsBrake();

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
