#ifndef MOVEMENT_TOOLS_HPP
#define MOVEMENT_TOOLS_HPP

#include "main.h"

extern bool touchHang;
void touchHangToggle(bool touch);

void moveToPoint(double targetX, double targetY, int maxMilliseconds = 60000, int voltage = 127);
void moveRelative(double tiles, int maxMilliseconds = 60000, int voltage = 127);

void turnRelative(double degrees, int maxMilliseconds = 60000, int voltage = 127);
void turnAbsolute(double degrees, int maxMilliseconds = 60000, int voltage = 127);

#endif