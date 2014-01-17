#include "WPILib.h"
#ifndef __AUTONOMOUS__
#define __AUTONOMOUS__

class AutonomousDriver
{
public:
	AutonomousDriver();
	double GetDriveX();
	double GetDriveY();
	double GetDriveR();
	bool ShouldShoot();
	bool ShouldStartAiming();
};
#endif
