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
	wings.setLeft(true);
	pros::delay(250);
	turnRelative(225, 2000);
	turnAbsolute(225, 500);
	wings.setLeft(false);

	// Touch hang
	moveRelative(0.4, 700);
	turnAbsolute(-90, 700);
	intake.spin(-127);
	moveRelative(1.1, 1000);
	pros::delay(1000);
	intake.spin(0);
}

void nearAuton() {
	// Shoot ally triball towards goal
	wings.setLeft(true);
	pros::delay(250);
	wings.setLeft(false);

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
	wings.setRight(true);
	moveRelative(0.6, 700);
	turnAbsolute(-105+20, 600);

	// Push triballs across hang
	intake.spin(-127);
	moveRelative(1, 900);
	wings.setRight(false);
	turnAbsolute(-80+20, 600);
	wings.setRight(true);
	moveRelative(0.72, 1000);
	pros::delay(500);
	wings.setRight(false);
	intake.spin(0);
}

void nearAutonElims() {
	// Shoot ally triball towards goal
	wings.setLeft(true);
	pros::delay(250);
	wings.setLeft(false);

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
	wings.setRight(true);
	moveRelative(0.6, 700);
	turnAbsolute(-105+20, 600);

	// Push triballs across hang
	intake.spin(-127);
	moveRelative(1, 900);
	wings.setRight(false);
	turnAbsolute(-80+20, 600);
	wings.setRight(true);
	moveRelative(0.72, 1000);
	pros::delay(500);
	wings.setRight(false);
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
	wings.setLeft(true);
	wings.setRight(true);
	moveRelative(0.75, 600);

	// Score triballs
	turnAbsolute(-100, 500);
	wings.setRight(false);
	turnAbsolute(-165, 600);
	wings.setLeft(false);
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
	wings.setLeft(true);
	wings.setRight(true);
	moveRelative(1.5, 1000);
	wings.setLeft(false);
	wings.setRight(false);
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
const int MATCHLOADING_TIME = 30000;
void prgmSkills() {
	puncher.setBrakeMode(MOTOR_BRAKE_HOLD);
	// Set up for launching
	moveRelative(-0.35, 500);
	turnAbsolute(-74+135, 800);
	moveRelative(-0.18, 500);
	// lift.toggle();
	int puncherStart = pros::millis();
	puncher.toggleManual();
	while ((puncherStart + MATCHLOADING_TIME) > pros::millis()) {
		puncher.move();
	}
	puncher.toggleManual();

	// Move to opposite side
	// lift.toggle();
	puncher.retract();
	turnAbsolute(-135+135, 700);
	moveRelative(0.6, 700);
	turnAbsolute(-90+136, 900);
	moveRelative(3.4, 2400);

	// Shove side face of goal
	turnAbsolute(-40+135, 1000);
	wings.setLeft(true);
	moveRelative(2, 1600, 90);
	wings.setLeft(false);
	moveRelative(-0.6, 1000);
	moveRelative(2, 1600);
	moveRelative(-0.6, 1000);
	turnAbsolute(0+135, 1000);

	// Shove first face of goal
	turnAbsolute(55+135, 600);
	moveRelative(1.8, 1500);
	turnAbsolute(-75+135, 1000);
	wings.setLeft(true);
	wings.setRight(true);
	moveRelative(2, 1500, 80);
	wings.setLeft(false);
	wings.setRight(false);

	// Shove second face of goal
	turnAbsolute(-90+135, 100);
	moveRelative(-1.4, 1000);
	turnAbsolute(0+135, 1000);
	moveRelative(1.4, 1000);
	turnAbsolute(-135+135, 1000);

	wings.setLeft(true);
	wings.setRight(true);
	moveRelative(2.5, 2000, 80);
	wings.setLeft(false);
	wings.setRight(false);

	moveRelative(-0.7, 1500);
}
