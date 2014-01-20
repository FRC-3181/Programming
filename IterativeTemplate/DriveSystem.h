#include "WPILib.h"
#ifndef __DRIVE__
#define __DRIVE__

class DriveSystem
{
public:
	void drive(); //Adjust the wheel values to whatever the controls request
	static double gyroAngle();//Deterimine the angle that we have turned
};
#endif
