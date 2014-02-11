#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{

public:
	RobotDemo()
	{
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl()
	{
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Robot Enabled");
		DriverStationLCD::GetInstance()->UpdateLCD();
		Wait(5);				// wait for a motor update time

		Talon *motor=new Talon(7);
		Talon *motor2=new Talon(8);
		motor->Set(1);
				motor2->Set(1);
				DriverStationLCD::GetInstance()->Clear();
				DriverStationLCD::GetInstance()->UpdateLCD();

				Wait(5);				// wait for a motor update time
				motor->Set(-1);
								motor2->Set(-1);
								Wait(5);				// wait for a motor update time
								motor->Set(0);
																motor2->Set(0);
																Wait(500);				// wait for a motor update time

																		
		/*
		Talon *motor3=new Talon(3);
		Talon *motor4=new Talon(4);
/*
		motor->Set(0.5);
		motor2->Set(0.5);
		Wait(10);				// wait for a motor update time
		motor->Set(0);
		motor2->Set(0);
		Wait(1000);				// wait for a motor update time

		while (IsOperatorControl())
		{
			motor->Set(0.5);
			motor2->Set(0.5);
			motor3->Set(0.5);
			motor4->Set(0.5);

		}*/
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

