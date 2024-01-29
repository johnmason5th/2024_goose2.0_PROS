#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include "main.h"


// Controller
extern bool controllerScreenEnabled;
extern int driverControlStartTime;
void printController(void* param);

// Exponential Joystick
int exponentialJoystick(int joystick);

// LCD
extern bool leftButtonPressed;
void on_left_button_lcd();
void on_center_button_lcd();
void on_right_button_lcd();


#endif