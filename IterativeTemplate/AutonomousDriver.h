#include "WPILib.h"
#ifndef __AUTONOMOUS__
#define __AUTONOMOUS__

class AutonomousDriver
{
public:
	AutonomousDriver();
	void startTimer();
	double GetDriveY();//Get the Y value for driving
	bool ShouldShoot();//Should we fire the ball
private:
	Timer *driveTimer;
};
#endif
