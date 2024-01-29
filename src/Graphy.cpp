#include "main.h"

// Create graphy
std::shared_ptr<graphy::AsyncGrapher> grapher(new graphy::AsyncGrapher("Drivetrain Velocity vs. Time"));

void graphing(void* ignore) {
	// Update graphy data
	grapher->update("Desired Vel", 0);
	grapher->update("Actual Vel", 0);
}

// void graphy(void* param) {
//     double DESIRED_VELOCITY = (char*)param;
// }