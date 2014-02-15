#include "WPILib.h"
#include "AutonomousDriver.h"
#ifndef __CONTROL__
#define __CONTROL__

class Controls
{
public:
	static void Init(); //Sets up Joysticks, etc.
	static bool IsAutonomous; //Is the Robot is in autonomous mode
	static AutonomousDriver* AutoDriver;//Fake driver for autnomous Mode
	//Drive System
	static double GetDriveX(); //X value for driving
	static double GetDriveY(); //Y value for driving
	static double GetDriveR(); //Rotation for driving
	static bool GetGyroReset();//Reset Gyro?
	//Shooter  and Collector
	static double GetCollectorSpin();//Driver pressed buttons spin collector
	static double GetCollectorRaise();//Driver pressed buttons to raise and lower collector
	static bool GetFireButton(); //Driver pressed the button to shoot at the target
        static bool GetPassButton(); //Driver pressed the button to shoot at the target


	
private:
	static double GetDriveThrottle();//Amount drive Values are throttled
	//Controls for the driver
	static Joystick* DriveStick;//Joystick
	static Joystick* BallStick;//Joystick for Ball Handling


};
#endif
