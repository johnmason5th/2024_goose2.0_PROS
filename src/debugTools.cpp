#include "main.h"

void debugDrivetrainEncoders() {
	pros::delay(40);
	controller.clear();
	std::string str = "";
	str = std::to_string((int)leftDT.get_positions()[0])+" ";
	str += std::to_string((int)leftDT.get_positions()[1])+" ";
	str += std::to_string((int)leftDT.get_positions()[2]);
	pros::delay(50);
	controller.print(0,0,str.c_str());
	str = std::to_string((int)rightDT.get_positions()[0])+" ";
	str += std::to_string((int)rightDT.get_positions()[1])+" ";
	str += std::to_string((int)rightDT.get_positions()[2]);
	pros::delay(50);
	controller.print(1,0,str.c_str());
}