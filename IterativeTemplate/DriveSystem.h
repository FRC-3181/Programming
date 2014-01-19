#include "WPILib.h"
#ifndef __DRIVE__
#define __DRIVE__

class DriveSystem
{
public:
	void drive();
	static double gyroAngle();
};
#endif
