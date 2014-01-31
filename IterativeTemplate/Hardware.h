#include "WPILib.h"
#ifndef __HARDWARE__
#define __HARDWARE__


enum speedControllerType { //Type of speedcontroller for reversable Speed controller
	victor = 0, //not shooting
	jaguar=1, //Releasing ball
	talon=2, //Waiting while ball leaves
};
class ReversableSpeedController{
public:
	ReversableSpeedController(speedControllerType controllerType,int channel,bool isReversed);
	float Get();
	void Set(float value);
private:
	SpeedController *controller;
	bool isReversed;
};


class Hardware
{
public:
	static ReversableSpeedController *DriveFL;//Front left drive motor speed controller
	static ReversableSpeedController *DriveBL;//Back left drive motor speed controller
	static ReversableSpeedController *DriveFR;//Front right drive motor speed controller
	static ReversableSpeedController *DriveBR;//Back right drive motor speed controller
	static ReversableSpeedController *ShooterMotor;//speed controller for shooting
	static ReversableSpeedController *CollectorSpin;//speed controller for shooting
	static ReversableSpeedController *CollectorRaise;//speed controller for shooting

	static Gyro * DriveGyro;//Gyro for measuring how much we have turned
	static Encoder * someEncoder;//Don't know what this is (Robbie)
	
	static void Init();
};

#endif
