#include "main.h"

void debugDrivetrainEncoders() {
	pros::delay(40);
	controller.clear();
	std::string str = "";
	str = std::to_string((int)left1.get_position())+" ";
	str += std::to_string((int)left2.get_position())+" ";
	str += std::to_string((int)left3.get_position());
	pros::delay(50);
	controller.print(0,0,str.c_str());
	str = std::to_string((int)right1.get_position())+" ";
	str += std::to_string((int)right2.get_position())+" ";
	str += std::to_string((int)right3.get_position());
	pros::delay(50);
	controller.print(1,0,str.c_str());
}