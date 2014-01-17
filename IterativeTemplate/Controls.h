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
	static bool GetShootOverTruss();
	static bool GetShootAtTarget();
	static bool GetAiming();
	static void EndAiming();
	
private:
	static Joystick *driveStick;
	static Joystick *auxStick;
	static AutonomousDriver *autoDriver;
	static double GetDriveThrottle();
	static bool isAiming;
	static bool canCancelAim;

};
#endif
