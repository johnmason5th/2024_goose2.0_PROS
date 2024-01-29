#include "odometry.hpp"

// 10.375 inches dt width, center of wheel-to-wheel
// 5.1875
const float LEFT_TRACKER_DIST = 5.1875;
const float RIGHT_TRACKER_DIST = 5.1875;
const float PERP_TRACKER_DIST = 0;

const float LEFT_TRACKER_WHEEL_DIA = 3.25;
const float RIGHT_TRACKER_WHEEL_DIA = 3.25;
const float PERP_TRACKER_WHEEL_DIA = 0;

bool odomEnabled = true;

int prevLeftEncoderVal = 0;
int prevRightEncoderVal = 0;
int prevPerpEncoderVal = 0;
float prevOrientation = 0;
void odometry(void* param) {
	while(true) {
		if(!odomEnabled) continue;
		//Get encoder values and assign to variables
		int leftEncoderVal = left2.get_position();
		int rightEncoderVal = right1.get_position();
		int perpEncoderVal = 0;
		
		int leftEncoderChange = leftEncoderVal - prevLeftEncoderVal;
		int rightEncoderChange = rightEncoderVal - prevRightEncoderVal;
		int perpEncoderChange = perpEncoderVal - prevPerpEncoderVal;

		prevLeftEncoderVal = leftEncoderVal;
		prevRightEncoderVal = rightEncoderVal;
		prevPerpEncoderVal = perpEncoderVal;

		prevOrientation = g_robotHeading;

		float leftTrackerTravel = (float)leftEncoderChange * (LEFT_TRACKER_WHEEL_DIA*PI/360);
		float rightTrackerTravel = (float)rightEncoderChange * (RIGHT_TRACKER_WHEEL_DIA*PI/360);
		float perpTrackerTravel = (float)perpEncoderChange * (PERP_TRACKER_WHEEL_DIA*PI/360);

		float headingChange = inertialSensor.get_rotation() - prevOrientation;

		float localOffsetX;
		float localOffsetY;
		if(headingChange == 0) {
			localOffsetX = perpTrackerTravel;
			localOffsetY = rightTrackerTravel;
		} else {
			localOffsetX = 2*sin(headingChange/2)*(perpTrackerTravel/headingChange+PERP_TRACKER_DIST);
			localOffsetY = 2*sin(headingChange/2)*(rightTrackerTravel/headingChange+RIGHT_TRACKER_DIST);
		}
		
		g_robotHeading += headingChange;

		float globalRadius = sqrt(localOffsetX*localOffsetX+localOffsetY*localOffsetY);
		float globalAngle = g_robotHeading - atan2(localOffsetY,localOffsetX);

		float globalOffsetX = cos(globalAngle) * globalRadius;
		float globalOffsetY = sin(globalAngle) * globalRadius;

		g_robotX += globalOffsetX/24; // inches to tiles
		g_robotY -= globalOffsetY/24;

		// pros::lcd::set_text(1, "X: "+std::to_string(g_robotX)+"in");
		// pros::lcd::set_text(2, "Y: "+std::to_string(g_robotY)+"in");
		// pros::lcd::set_text(3, "Angle: "+std::to_string(g_robotOrientation*(180/PI))+"deg");
		
		pros::delay(10);
	}
}
