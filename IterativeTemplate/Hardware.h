#include "WPILib.h"
#ifndef __HARDWARE__
#define __HARDWARE__

class Hardware
{
public:
	static SpeedController *DriveFL;
	static SpeedController *DriveBL;
	static SpeedController *DriveFR;
	static SpeedController *DriveBR;
	static SpeedController *ShooterMotor;
	static Gyro * DriveGyro;
	static Encoder * someEncoder;//Don't know what this is (Robbie)
	
	static void Init();
};
#endif
