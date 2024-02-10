#ifndef PUNCHER_HPP
#define PUNCHER_HPP

#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include "pros/distance.hpp"
#include <string>

class Puncher {
    private:
        pros::Motor* motor11;
        pros::Motor* motor5_5;
        pros::Rotation* rotationSensor;
        pros::Distance* distanceSensor;
        bool retracted;
        bool loaded;
        const int TUCK_ANGLE;
        const int DIST_SENSOR_DIST;
        const int WAIT_SINCE_LOADED;
        int timeAtLoad;
        std::string mode;
        bool manual;
        bool enabled;
        bool relaxed;
    public:
        Puncher(pros::Motor* motor11, pros::Motor* motor5_5, pros::Rotation* rotationSensor, pros::Distance* distanceSensor);
        void brake();
        void setVoltage(int volt);
        void toggleManual();
        void retract();
        void moveAuto();
        void move();
        void disable(bool value);
        void relax(bool value);
        void setBrakeMode(pros::motor_brake_mode_e brakeMode);
};

#endif