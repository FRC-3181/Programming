#include "WPILib.h"
#include "DriveSystem.h"
#include "Shooter.h"
#include "BallCollector.h"
#ifndef __HARDWARE__
#define __HARDWARE__


class Hardware
{
public:
	static DriveSystem* DriveSys;//Drive System
	static Shooter* BallShooter;//Shooter
	static BallCollector* Collector;//Ball Collector

	static void Init();
	
private:
	//Drive System Motors and Sensors
	static SpeedController* DriveFL;
	static SpeedController* DriveBL;
	static SpeedController* DriveFR;
	static SpeedController* DriveBR;
	static Gyro * DriveGyro;
	
	//Shooter Motors and Sensors
	static SpeedController* ShooterLeft;
	static SpeedController* ShooterRight;
	static AnalogChannel* ShotPotentiometer;
	static DigitalInput* UpperLimit;
	static DigitalInput* LowerLimit;


	//Collector Motors
	static SpeedController* CollectorSpinL;
	static SpeedController* CollectorSpinR;
	static SpeedController* CollectorRaise;
};

#endif
