#include "WPILib.h"
#include "Hardware.h"
#include "Controls.h"
#include "DriveSystem.h"
#include "Shooter.h"
#include "BallCollector.h"
/**
 * This is a demo program showing the use of the RobotBase class.
 * The IterativeRobot class is the base of a robot application that will automatically call your
 * Periodic methods for each packet based on the mode.
 */ 

class RobotDemo : public IterativeRobot
{
public:
	RobotDemo()
	{
		this->SetPeriod(0); 	//Set update period to sync with robot control packets (20ms nominal)
	}

	/**
	* Robot-wide initialization code should go here.
	* 
	* Use this method for default Robot-wide initialization which will
	* be called when the robot is first powered on.  It will be called exactly 1 time.
	*/
	void RobotDemo::RobotInit()
	{
		Hardware::Init();
		Controls::Init();

	}
	
	/**
	* Initialization code for disabled mode should go here.
	* 
	* Use this method for initialization code which will be called each time
	* the robot enters disabled mode. 
	*/
	void RobotDemo::DisabledInit()
	{
	}
	
	/**
	* Periodic code for disabled mode should go here.
	* 
	* Use this method for code which will be called periodically at a regular
	* rate while the robot is in disabled mode.
	*/
	void RobotDemo::DisabledPeriodic()
	{
	}
	
	/**
	* Initialization code for autonomous mode should go here.
	* 
	* Use this method for initialization code which will be called each time
	* the robot enters autonomous mode.
	*/
	void RobotDemo::AutonomousInit()
	{
		Controls::isAutonomous=true;
	}
	
	/**
	* Periodic code for autonomous mode should go here.
	*
	* Use this method for code which will be called periodically at a regular
	* rate while the robot is in autonomous mode.
	*/
	void RobotDemo::AutonomousPeriodic()
	{
		Controls::autoDriver->drive();
		Hardware::driveSys->drive();
		Hardware::shooter->shoot();
	}
	
	/**
	* Initialization code for teleop mode should go here.
	* 
	* Use this method for initialization code which will be called each time
	* the robot enters teleop mode.
	*/
	void RobotDemo::TeleopInit()
	{
		Controls::isAutonomous=false;
	}
	
	/**
	* Periodic code for teleop mode should go here.
	*
	* Use this method for code which will be called periodically at a regular
	* rate while the robot is in teleop mode.
	*/
	void RobotDemo::TeleopPeriodic()
	{
		Hardware::driveSys->drive();//Tell Drive System to drive robot
		Hardware::shooter->shoot(); //Tell shooter to shoot if needed
		Hardware::collector->collect(); //Tell Collector to collect
	}
	
	/**
	* Initialization code for test mode should go here.
	* 
	* Use this method for initialization code which will be called each time
	* the robot enters test mode.
	*/
	void RobotDemo::TestInit()
	{
		Controls::isAutonomous=false;
	}
	
	/**
	* Periodic code for test mode should go here.
	*
	* Use this method for code which will be called periodically at a regular
	* rate while the robot is in test mode.
	*/
	void RobotDemo::TestPeriodic()
	{
		
	}
	
};

START_ROBOT_CLASS(RobotDemo);

