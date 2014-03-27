#include "WPILib.h"999999**999*9999999-9*9-999-**99999999999999999-***-**9-
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
	          Hardware::RobotLights->SetUnderGlow(UnderGlow::WHITE,false);
	              DriverStationLCD::GetInstance()->Clear();
	                    DriverStationLCD::GetInstance()->UpdateLCD();

	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
	  switch(DriverStation::GetInstance()->GetAlliance()){
	            case DriverStation::kRed:{
	              Hardware::RobotLights->SetUnderGlow(UnderGlow::RED,false);
	            }break;
	            case DriverStation::kBlue:{
	              Hardware::RobotLights->SetUnderGlow(UnderGlow::BLUE,false); 
	                      }break;
	            default:{
	              Hardware::RobotLights->SetUnderGlow(UnderGlow::OFF,false);        
	                      }break;
	            }
	  Hardware::Collector->AutonomousCollect(0.2,1);
       //   Wait(3);
	  Hardware::DriveSys->DriveForward(0.5,2.5);
          Hardware::DriveSys->DriveForward(0,0.5);
          Hardware::Shooter->AutonomousShoot(this);

	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	

	void OperatorControl()
	{
	  DriverStationLCD::GetInstance()->Clear();
	 DriverStationLCD::GetInstance()->UpdateLCD();
          
          bool buttonState=false;
          bool LSDMode=false;
		while (IsOperatorControl() && IsEnabled())
		{
		    
		    if(!buttonState&&Hardware::DriveSys->stick->GetRawButton(7))LSDMode=!LSDMode;
		    buttonState=Hardware::DriveSys->stick->GetRawButton(7);

                        Hardware::RobotLights->LSDSimulator(LSDMode);

		          Hardware::DriveSys->Drive();
	                    Hardware::Collector->Collect();

	                    Hardware::Shooter->Shoot();
		           
		   float voltage=Hardware::RangeFinder->GetVoltage();
		   float v=int(voltage*100)/100;
		   float dist=v/0.108;
		   int feet=int(dist);
		   int inch=int(dist*12)%12;
		  DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line3,"Distance: %i ft %i in",feet,inch);
		  DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line6,"Ultrasonic: %f V",Hardware::RangeFinder->GetVoltage());
		                    
		  SmartDashboard::PutNumber("Dist",dist); 
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

