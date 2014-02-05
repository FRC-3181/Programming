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
	static SpeedController *ShooterLeft;//Left speed controller for shooting
	static SpeedController *ShooterRight;//Right Speed Controller for shooting
	static SpeedController *CollectorSpinL;//Left speed controller for collecting
	static SpeedController *CollectorSpinR;//Right speed controller for collecting
	static SpeedController *CollectorRaise;//Raise/Lower speed controller for collecting


	static Gyro * DriveGyro;//Gyro for measuring how much we have turned
	static AnalogChannel *shotPot;//Potentiometer for measuring shooting

	
	static void Init();
};

#endif
