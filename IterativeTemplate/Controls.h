#include "WPILib.h"
#include "AutonomousDriver.h"
#ifndef __CONTROL__
#define __CONTROL__

class Controls
{
public:
	static void Init(); //Sets up Joysticks, etc.
	static bool isAutonomous; //Is the Robot is in autonomous mode
	static AutonomousDriver *autoDriver;//Fake driver for autnomous Mode
	//Drive System
	static double GetDriveX(); //X value for driving
	static double GetDriveY(); //Y value for driving
	static double GetDriveR(); //Rotation for driving
	static bool GetGyroReset();//Reset Gyro?
	//Shooter  and Collector
	static bool GetCollectorButton();//Driver pressed button to pick up a ball.
	static bool GetRejectButton();//Driver pressed button to pick up a ball.
	static bool GetFireButton(); //Driver pressed the button to shoot at the target
	static bool IsTrussMode(); //Driver pressed the button to shoot over the truss
	static bool IsTargetMode(); //Robot is in Aiming/Shooting Mode
	static void SetFireLED(bool); //Turn Fire LED off

	
private:
	static double GetDriveThrottle();//Amount drive Values are throttled
	//Controls for the driver
	static Joystick *driveStick;//Joystick
	static DriverSationEnhancedIO *auxIO;//Cypress Module

};
#endif
