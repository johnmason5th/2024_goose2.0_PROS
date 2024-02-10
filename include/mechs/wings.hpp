#ifndef WINGS_HPP
#define WINGS_HPP

#include "pros/adi.hpp"

class Wings {
    private:
        pros::ADIDigitalOut* leftSolenoid;
        pros::ADIDigitalOut* rightSolenoid;
        bool extended;
    public:
        Wings(pros::ADIDigitalOut* leftSolenoid, pros::ADIDigitalOut* rightSolenoid);
        void toggle();
        void setLeft(bool value);
        void setRight(bool value);
};

#endif