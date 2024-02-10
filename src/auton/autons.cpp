#include "autons.hpp"

/**
 * Grab center triball
 * Remove mlz triball
 * score ally triball
 * dump all 3 (or 2 if hang is off limits) triballs on other side of hang
 * make it optional that we touch hang or not
*/
// Starts at angle of -20 relative to field
// Place at angle of -21 for some reason
void nearAuton() {
	// Shoot ally triball towards goal
	wings.setLeft(true);
	pros::delay(250);
	wings.setLeft(false);

	// Grab Triball
	intake.move(127);
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
	intake.move(-127);
	moveRelative(1, 900);
	wings.setRight(false);
	turnAbsolute(-80+20, 600);
	wings.setRight(true);
	moveRelative(0.72, 1000);
	pros::delay(500);
	wings.setRight(false);
	intake.move(0);
}

void nearAutonElims() {
	// Shoot ally triball towards goal
	wings.setLeft(true);
	pros::delay(250);
	wings.setLeft(false);

	// Grab Triball
	intake.move(127);
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
	intake.move(-127);
	moveRelative(1, 900);
	wings.setRight(false);
	turnAbsolute(-80+20, 600);
	wings.setRight(true);
	moveRelative(0.72, 1000);
	pros::delay(500);
	wings.setRight(false);
	intake.move(0);

	// Go to MLZ
	moveRelative(-1.4, 1000);
}

// -35
void farAuton() {
	// Grab hang triball
	intake.move(127);
	moveRelative(0.42, 600, 90);
	pros::delay(100);

	// Get MLZ triball
	moveRelative(-1.3, 800);
	turnAbsolute(-139, 1000);
	intake.move(-127);
	wings.setLeft(true);
	wings.setRight(true);
	moveRelative(0.75, 600);

	// Score triballs
	turnAbsolute(-100, 500);
	wings.setRight(false);
	turnAbsolute(-165, 600);
	moveRelative(0.55, 600);
	turnAbsolute(-92, 550);
	wings.setLeft(false);
	intake.move(-127);
	moveRelative(1.2, 650);

	// Grab Close Barrier Triball
	turnAbsolute(-90, 400);
	moveRelative(-0.64, 800);
	turnAbsolute(-13, 550);
	intake.move(127);
	moveRelative(2, 1150);
	turnAbsolute(-160, 650);
	intake.move(-60);
	moveRelative(0.64, 650);

	// Grab Far Barrier Triball
	intake.move(127);
	turnAbsolute(-30, 550);
	moveRelative(1.02, 800);
	turnAbsolute(-190, 800, 110);
	intake.move(-50);
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
const int MATCHLOADING_TIME = 32000;
void prgmSkills() {
	puncher.setBrakeMode(MOTOR_BRAKE_HOLD);
	// Set up for launching
	moveRelative(-0.25, 500);
	turnAbsolute(-75+135, 800);
	moveRelative(-0.2, 500);
	lift.setExtended(true);
	int puncherStart = pros::millis();
	while ((puncherStart + MATCHLOADING_TIME) > pros::millis()) {
		puncher.move();
	}

	// Move to opposite side
	lift.setExtended(false);
	puncher.retract();
	turnAbsolute(-135+135, 700);
	moveRelative(0.5, 700);
	turnAbsolute(-90+135, 700);
	moveRelative(3.2, 2000);

	// Shove side face of goal
	turnAbsolute(-20+135, 1000);
	moveRelative(2, 1500);
	moveRelative(-0.5, 800);

	// Shove first face of goal
	turnAbsolute(45+135, 600);
	moveRelative(2.4, 1500);
	turnAbsolute(-90+135, 1000);
	wings.setLeft(true);
	wings.setRight(true);
	moveRelative(2, 1500);
	wings.setLeft(false);
	wings.setRight(false);

	// Shove second face of goal
	moveRelative(-1.4, 1000);
	turnAbsolute(0+135, 1000);
	moveRelative(0.5, 1000);
	turnAbsolute(-90+135, 1000);

	wings.setLeft(true);
	wings.setRight(true);
	moveRelative(2, 2000);
	wings.setLeft(false);
	wings.setRight(false);

	moveRelative(-1.4, 1500);
}
