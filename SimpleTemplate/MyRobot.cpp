#include "WPILib.h"
#include "Hardware.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
const double RSPEED=0.25;
        const double SSPEED=0.25;
class RobotDemo : public SimpleRobot
{

public:
	RobotDemo()
	{
	  Hardware::Init();
	 // Hardware::RobotLights->setUnderGlow(false,false,true);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
          Hardware::DriveSys->DriveForward(0.5,3.0);
          Hardware::Shooter->AutonomousShoot(this);

	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	
	
	void OperatorControl()
	{
	  
	  DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Variable Shooter Enabled");
	 
		while (IsOperatorControl() && IsEnabled())
		{
		    Hardware::DriveSys->Drive();
		      Hardware::Shooter->Shoot();
		      Hardware::Collector->Collect();
		      DriverStationLCD::GetInstance()->UpdateLCD();

			Wait(0.005);				// wait for a motor update time
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

