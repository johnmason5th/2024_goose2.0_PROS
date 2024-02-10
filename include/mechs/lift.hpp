#ifndef LIFT_HPP
#define LIFT_HPP

#include "pros/adi.hpp"

class Lift {
    private:
        pros::ADIDigitalOut* solenoid;
        bool extended;
        bool enabled;
    public:
        Lift(pros::ADIDigitalOut* solenoid);
        void toggle();
        void setExtended(bool value);
        void disable();
};

#endif