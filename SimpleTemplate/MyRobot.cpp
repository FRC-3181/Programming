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
	 // 
	  
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
	  switch(DriverStation::GetInstance()->GetAlliance()){
	            case DriverStation::kRed:{
	              Hardware::RobotLights->SetUnderGlow(UnderGlow::RED);
	            }break;
	            case DriverStation::kBlue:{
	              Hardware::RobotLights->SetUnderGlow(UnderGlow::BLUE); 
	                      }break;
	            default:{
	              Hardware::RobotLights->SetUnderGlow(UnderGlow::OFF);        
	                      }break;
	            }
	  Hardware::Collector->AutonomousCollect(0.2,1);
          Hardware::DriveSys->DriveForward(0.3,0.75);
          Hardware::DriveSys->DriveForward(0,1);
          Hardware::Shooter->AutonomousShoot(this);

	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	
	
	void OperatorControl()
	{
	  Hardware::RobotLights->SetUnderGlow(UnderGlow::WHITE);
	  DriverStationLCD::GetInstance()->Clear();
		while (IsOperatorControl() && IsEnabled())
		{
		    Hardware::DriveSys->Drive();
	                Hardware::Collector->Collect();
	                
		      Hardware::Shooter->Shoot();
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

