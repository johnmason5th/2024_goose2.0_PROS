#ifndef WINGS_HPP
#define WINGS_HPP

#include "pros/adi.hpp"

class Wings {
    private:
        pros::ADIDigitalOut* solenoid;
        bool extended;
    public:
        Wings(pros::ADIDigitalOut* solenoid);
        void toggle();
        void extend(bool value);
};

#endif