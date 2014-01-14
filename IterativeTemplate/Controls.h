#include "WPILib.h"
#include "AutonomousDriver.h"
#ifndef __CONTROL__
#define __CONTROL__

class Controls
{
public:
	static void Init();
	static bool isAutonomous;
	static double GetDriveX();
	static double GetDriveY();
	static double GetDriveR();
private:
	static Joystick *driveStick;
	static Joystick *auxStick;
	static AutonomousDriver *autoDriver;
	static double GetDriveThrottle();
};
#endif
