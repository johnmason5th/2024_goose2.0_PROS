#ifndef MECHS_HPP
#define MECHS_HPP

#include "main.h"

void setDrivetrainBrakeMode(pros::motor_brake_mode_e brakeMode);

void drivetrain();

void intake();

void on_left_button_lcd();
void on_center_button_lcd();
void on_right_button_lcd();

void puncherMotorsBrake();
void puncherMotorsVolt(int volt);
void puncherWithRot();
void puncherDumb();

void wings();

void lift();

void hang();

#endif