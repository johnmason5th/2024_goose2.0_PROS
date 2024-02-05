#include "main.h"
// 1:Near  2:Far  3:Skills
const int AUTON_TYPE = 3;

/*
## Changes To Do ##
- Make Mechs all objects, to make accessing through auton easier and make more sense
- 
Done - Skills, auton, use distance sensor
Done - Kaboomer releases, puncher releases

## Innovations ##
- Forward backward stick, even if joystick turned a little, leave at full power
	- driver accidentally turns unintentionally
*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
const bool ENABLE_LCD = true;
const bool ENABLE_GRAPHY = false;
void initialize() {
	puncherMotor11.set_brake_mode(MOTOR_BRAKE_HOLD);
	puncherMotor5_5.set_brake_mode(MOTOR_BRAKE_HOLD);

	controller.clear();
	pros::delay(50);
	controller.print(1,0,"Calibrating");
	pros::delay(50);
	controller.print(2,0,"IMU...");

	inertialSensor.reset(true);
	pros::delay(2500);
	controller.clear();
	pros::delay(50);
	controller.print(1, 0, (inertialSensor.get_rotation() == INFINITY)?"IMU Error":"IMU Functional");
	pros::delay(50);
	controller.print(2, 0, (std::to_string(inertialSensor.get_rotation())).c_str());
	pros::delay(250);
	controller.clear();
	
	if (ENABLE_LCD) {
		pros::lcd::initialize();
		pros::lcd::set_background_color(LV_COLOR_BLACK);
		pros::lcd::print(7, "Near    None    Far");
		pros::lcd::register_btn0_cb(on_left_button_lcd);
		pros::lcd::register_btn1_cb(on_center_button_lcd);
		pros::lcd::register_btn2_cb(on_right_button_lcd);
	} else if (ENABLE_GRAPHY) { // 'else' just in case running both is bad
		// Add data types
		grapher->addDataType("Desired Vel", COLOR_ORANGE);
		grapher->addDataType("Actual Vel", COLOR_AQUAMARINE);

		// Start graphy task
		grapher->startTask();
	}
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	pros::Task odomTask(odometry);
	// pros::Task grapherTask(graphing);
	setDrivetrainBrakeMode(MOTOR_BRAKE_HOLD);
	// Autons
	switch (AUTON_TYPE) {
		case 1:
			nearAuton();
			break;
		case 2:
			farAuton();
			break;
		case 3:
			prgmSkills();
			break;
		default:
			pushAuton();
	}

	odomEnabled = false;
	setDrivetrainBrakeMode(MOTOR_BRAKE_COAST);
	pros::delay(200);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
bool manualPuncher = false;
void opcontrol() {
	pros::Task controllerScreen(printController);
	driverControlStartTime = pros::millis();
	setDrivetrainBrakeMode(MOTOR_BRAKE_COAST);
	// Main Loop
	while(true) {
		drivetrain();
		intake();
		if (controller.get_digital_new_press(DIGITAL_Y)) {
			manualPuncher = !manualPuncher;
		}
		if (manualPuncher) {
			puncherMotorsVolt(127);
		} else {
			puncherWithRot();
		}
		wings();
		lift();
		hang();
		pros::delay(20);
	}
}
