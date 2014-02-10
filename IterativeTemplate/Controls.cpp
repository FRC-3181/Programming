#include "Controls.h"

//Set up stuff
Joystick* Controls::DriveStick = NULL;
bool Controls::IsAutonomous = false;

AutonomousDriver* Controls::AutoDriver = NULL;

const int GYRO_RESET_BUTTON = 6;

void Controls::Init()
{
	DriveStick = new Joystick(1); //Drive Joystick
	IsAutonomous = true;
	AutoDriver = new AutonomousDriver();
}
//Drive Stuff
double Controls::GetDriveX()//X value for driving (side to side)
{
	//If autonomous, ask the Autonomous driver. Otherwise get the throttle-adjusted X value from the Joystick
	return IsAutonomous ? 0 : GetDriveThrottle()* DriveStick->GetX();
}
double Controls::GetDriveY() //Y value for driving (forward and backward)
{
	//If we are aiming, there should be no Y value
	//If autonomous, ask the Autonomous driver. Otherwise get the throttle-adjusted Y value from the Joystick
	return IsAutonomous ? AutoDriver->GetDriveY() : GetDriveThrottle() * DriveStick->GetY();
}
double Controls::GetDriveR()//Rotation value for driving
{
	//If we are aiming, there should be no Rotation value
	//If autonomous, ask the Autonomous driver. Otherwise get the throttle-adjusted Rotation value from the Joystick
	return IsAutonomous ? 0 : GetDriveThrottle() * DriveStick->GetTwist();
}
bool Controls::GetGyroReset()
{
	return DriveStick->GetRawButton(GYRO_RESET_BUTTON);
} 
double Controls::GetDriveThrottle()//Throttle for drivng
{

	//Get Throttle returns -1 for full up and 1 for full down, convert this to 1 for full up and 0 for full down
	return (1 - DriveStick->GetThrottle()) / -2;
}
//Shooter and collector
bool Controls::GetFireButton()//Has the driver pressed the fire button
{
	//If we have are in Autonomous, ask the auto driver if we should fire
	//If we are in teleop, check the fire button
	return IsAutonomous ? AutoDriver->ShouldShoot() : DriveStick->GetTrigger();
}
int Controls::GetCollectorSpin()//Should we spin the collector?
{
	//check the button
	//DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line2,"%i",DriveStick->GetRawAxis(5));
	return DriveStick->GetRawAxis(5);
}
int Controls::GetCollectorRaise()//Should we raise the collector?
{
	//check the button
//	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line3,"%i",DriveStick->GetRawAxis(6));
//	DriverStationLCD::GetInstance()->UpdateLCD();
	return DriveStick->GetRawAxis(6);
}





















