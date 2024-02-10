#ifndef LIFT_HPP
#define LIFT_HPP

#include "pros/adi.hpp"
#include "mechs/puncher.hpp"

class Lift {
    private:
        pros::ADIDigitalOut* solenoid;
        Puncher* puncher;
        bool extended;
        bool enabled;
    public:
        Lift(pros::ADIDigitalOut* solenoid, Puncher* puncher);
        void toggle();
        void setExtended(bool value);
        void disable(bool value);
};

#endif