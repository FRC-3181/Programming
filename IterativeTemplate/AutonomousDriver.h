#include "WPILib.h"
#ifndef __AUTONOMOUS__
#define __AUTONOMOUS__

class AutonomousDriver
{
public:
	AutonomousDriver();
	void drive();
	double GetDriveX();//Get the X value for driving
	double GetDriveY();//Get the Y value for driving
	double GetDriveR();//Get the rotation for driving
	bool ShouldShoot();//Should we fire the ball
	bool ShouldStartAiming();//Should we begin aiming our shot
};
#endif
