#include "WPILib.h"
#ifndef __HARDWARE__
#define __HARDWARE__

class Hardware
{
public:
	static SpeedController *DriveFL;//Front left drive motor speed controller
	static SpeedController *DriveBL;//Back left drive motor speed controller
	static SpeedController *DriveFR;//Front right drive motor speed controller
	static SpeedController *DriveBR;//Back right drive motor speed controller
	static SpeedController *ShooterMotor;//speed controller for shooting
	static Gyro * DriveGyro;//Gyro for measuring how much we have turned
	static Encoder * someEncoder;//Don't know what this is (Robbie)
	
	static void Init();
};
#endif
