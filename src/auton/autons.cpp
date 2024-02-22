#include "autons.hpp"

/**
 * Grab center triball
 * Remove mlz triball
 * score ally triball
 * dump all 3 (or 2 if hang is off limits) triballs on other side of hang
 * make it optional that we touch hang or not
*/
// Maybe more consistent idea:
// Shoot ally triball towards goal, Descore MLZ ball, grab center triball, score ally triball, push triballs across hang
// Starts at angle of 0 relative to field
void nearAutonWinPoint() {
	// Descore MLZ ball & Shoot ally triball towards goal
	horizontalWings.extend(true);
	pros::delay(250);
	turnRelative(225, 2000);
	turnAbsolute(225, 500);
	horizontalWings.extend(false);

	// Touch hang
	moveRelative(0.4, 700);
	turnAbsolute(-90, 700);
	intake.spin(-127);
	moveRelative(1.1, 1000);
	pros::delay(1000);
	intake.spin(0);
}

// Set up at -21 degrees I guess
void nearAuton() {
	// Shoot ally triball towards goal
	horizontalWings.extend(true);
	pros::delay(200);
	horizontalWings.extend(false);

	// Grab Triball
	intake.spin(127);
	moveRelative(2.15, 1350);
	pros::delay(200);

	// Remove MLZ triball
	turnRelative(-13, 250);
	moveRelative(-2.11, 1350);
	verticalWings.extend(true);
	pros::delay(200);
	turnRelative(235, 900);
	verticalWings.extend(false);
	pros::delay(500);

	// Score ally triball
	turnAbsolute(-154+20, 750);
	moveRelative(-1, 1000);

	// Push triballs across hang
	turnAbsolute(180+20, 400);
	moveRelative(0.5, 600);
	turnAbsolute(-135+20, 500);
	moveRelative(0.95, 700);
	turnAbsolute(-85+20, 600);
	intake.spin(-127);
	moveRelative(1.4, 1200);
	pros::delay(500);
	intake.spin(0);
}

void nearAutonElims() {
	// Shoot ally triball towards goal
	horizontalWings.extend(true);
	pros::delay(250);
	horizontalWings.extend(false);

	// Grab Triball
	intake.spin(127);
	moveRelative(2, 1300);

	// Score ally triball
	moveRelative(-1.9, 1300);
	turnAbsolute(-157+20, 700);
	moveRelative(-1.3, 1000);

	// Remove MLZ triball
	turnAbsolute(177+20, 650);
	moveRelative(0.45, 700);
	turnAbsolute(-120+20, 700);
	horizontalWings.extend(true);
	moveRelative(0.6, 700);
	turnAbsolute(-105+20, 600);

	// Push triballs across hang
	intake.spin(-127);
	moveRelative(1, 900);
	horizontalWings.extend(false);
	turnAbsolute(-80+20, 600);
	horizontalWings.extend(true);
	moveRelative(0.72, 1000);
	pros::delay(500);
	horizontalWings.extend(false);
	intake.spin(0);

	// Go to MLZ
	moveRelative(-1.4, 1000);
}

// -35
void farAuton() {
	// Grab hang triball
	intake.spin(127);
	moveRelative(0.42, 600, 90);
	pros::delay(100);

	// Get MLZ triball
	moveRelative(-1.3, 800);
	turnAbsolute(-139, 1000);
	intake.spin(-127);
	horizontalWings.extend(true);
	horizontalWings.extend(true);
	moveRelative(0.75, 600);

	// Score triballs
	turnAbsolute(-100, 500);
	horizontalWings.extend(false);
	turnAbsolute(-165, 600);
	horizontalWings.extend(false);
	moveRelative(0.55, 600);
	turnAbsolute(-92, 550);
	intake.spin(-127);
	moveRelative(1.2, 650);

	// Grab Close Barrier Triball
	turnAbsolute(-90, 400);
	moveRelative(-0.64, 800);
	turnAbsolute(-13, 550);
	intake.spin(127);
	moveRelative(2, 1150);
	turnAbsolute(-160, 650);
	intake.spin(-60);
	moveRelative(0.64, 650);

	// Grab Far Barrier Triball
	intake.spin(127);
	turnAbsolute(-30, 550);
	moveRelative(1.02, 800);
	turnAbsolute(-190, 800, 110);
	intake.spin(-50);
	horizontalWings.extend(true);
	horizontalWings.extend(true);
	moveRelative(1.5, 1000);
	horizontalWings.extend(false);
	horizontalWings.extend(false);
	moveRelative(-0.5, 800);
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
// -135
const int MATCHLOADING_TIME = 25000;
void prgmSkills() {
	puncher.setBrakeMode(MOTOR_BRAKE_HOLD);
	// Set up for launching
	moveRelative(-0.35, 500);
	turnAbsolute(-75+135, 600);
	moveRelative(-0.14, 500);
	puncher.disable(false);
	int puncherStart = pros::millis();
	int triballCount = 0;
	while (((puncherStart + MATCHLOADING_TIME) > pros::millis()) || (triballCount >= 44)) {
		puncher.move();
	}

	// Move to opposite side
	puncher.retract();
	turnAbsolute(-135+135, 650);
	moveRelative(0.6, 650);
	turnAbsolute(-88+136, 550);
	moveRelative(3.4, 2100);

	// Shove side face of goal
	turnRelative(225, 2000);
	turnAbsolute(145+135, 300);
	moveRelative(-1.8, 1100);
	turnAbsolute(180+135, 600);
	moveRelative(0.5, 800);
	moveRelative(-2, 800);
	moveRelative(0.3, 1000);

	// Shove first face of goal
	turnAbsolute(80+135, 600);
	moveRelative(1.8, 1500);
	turnAbsolute(145+135, 800);
	verticalWings.extend(true);
	moveRelative(-2, 1500);
	turnAbsolute(90+135, 600);
	verticalWings.extend(false);
	moveRelative(0.8, 1000);
	turnAbsolute(100+135, 600);
	verticalWings.extend(true);
	moveRelative(-1.5, 1200);
	verticalWings.extend(false);

	// Shove second face of goal
	turnAbsolute(90+135, 100);
	moveRelative(1.3, 1000);
	turnAbsolute(0+135, 900);
	moveRelative(2.2, 1000);
	turnAbsolute(50+135, 600);
	verticalWings.extend(true);
	moveRelative(-2.2, 1500, 80);
	turnAbsolute(90+135, 600);
	verticalWings.extend(false);
	moveRelative(0.8, 1000, 80);
	verticalWings.extend(true);
	moveRelative(-1.5, 1200, 80);
	verticalWings.extend(false);

	moveRelative(0.7, 1500);
}
