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
	
	static void Init();
};
#endif
