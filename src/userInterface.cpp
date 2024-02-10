#include "userInterface.hpp"

// Controller Screen
bool controllerScreenEnabled = true;
int driverControlStartTime = 0;
void printController(void* param) {
	while (true) {
		if (!controllerScreenEnabled) continue;
		controller.print(0, 0, ("Btry: "+std::to_string((int)pros::battery::get_capacity()) + " Time: "+std::to_string((90000 - (pros::millis() - driverControlStartTime))/1000)).c_str());
		pros::delay(50);
		controller.print(1,0,("DT Temp: "+std::to_string((int)rightDT.get_temperatures()[0])).c_str());
		pros::delay(1000);
	}
}

// Exponential Joystick
int exponentialJoystick(int joystick) {
    return pow(joystick,3)/pow(127,2);
}

// LCD Screen Buttons
void on_left_button_lcd() {
	
}

void on_center_button_lcd() {

}

bool showPorts = false;
void on_right_button_lcd() {
	showPorts = !showPorts;
	if (showPorts) {
		pros::lcd::clear();
		pros::lcd::print(0, "LWing:A RWing:B");
		pros::lcd::print(1, "Lift:F Kaboomer:C");
		pros::lcd::print(2, "Intake:7 Inertial:15");
		pros::lcd::print(3, "Rotation:18 Distance:19");
		pros::lcd::print(4, "Puncher11:15 Puncher5_5:20");
		pros::lcd::print(5, "LeftDT:3,5,6 RightDT:1,2,4");
	}
}