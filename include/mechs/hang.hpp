#ifndef HANG_HPP
#define HANG_HPP

#include "pros/adi.hpp"
#include "lift.hpp"
#include "puncher.hpp"

class Hang {
    private:
        bool enabled;
        pros::ADIDigitalOut* solenoid;
        Lift* lift;
        Puncher* puncher;
    public:
        Hang(pros::ADIDigitalOut* solenoid, Lift* lift, Puncher* puncher);
        void toggle();
};

#endif