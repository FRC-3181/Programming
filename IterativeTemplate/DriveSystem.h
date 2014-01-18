#include "WPILib.h"
#ifndef __DRIVE__
#define __DRIVE__

class DriveSystem
{
public:
	void drive();
	static bool pointedAtTarget();
private:
	static double gyroAngle();
};
#endif
