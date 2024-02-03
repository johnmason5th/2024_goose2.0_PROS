#include "userInterface.hpp"

// Controller Screen
bool controllerScreenEnabled = true;
int driverControlStartTime = 0;
void printController(void* param) {
	while (true) {
		if (!controllerScreenEnabled) continue;
		controller.print(0, 0, ("Btry: "+std::to_string((int)pros::battery::get_capacity()) + " Time: "+std::to_string((90000 - (pros::millis() - driverControlStartTime))/1000)).c_str());
		pros::delay(50);
		controller.print(1,0,("Mtr Temp: "+std::to_string((int)rightDT.get_temperatures()[0])).c_str());
		pros::delay(1000);
	}
}

// Exponential Joystick
int exponentialJoystick(int joystick) {
    return pow(joystick,3)/pow(127,2);
}

// LCD Screen Buttons
bool leftButtonPressed = false;
void on_left_button_lcd() {
    leftButtonPressed = true;
    pros::lcd::print(2, ("Cata running: "+std::to_string(leftButtonPressed)).c_str());
}

void on_center_button_lcd() {}

void on_right_button_lcd() {}