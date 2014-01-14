#include "Controls.h"

Joystick *Controls::driveStick=NULL;
Joystick *Controls::auxStick=NULL;
bool Controls::isAutonomous=false;
AutonomousDriver *Controls::autoDriver=NULL;

void Controls::Init()
{
	driveStick=new Joystick(1);
	auxStick=new Joystick(2);
	isAutonomous=true;
	autoDriver=new AutonomousDriver();
}
double Controls::GetDriveX()
{
	return isAutonomous?autoDriver->GetDriveX():Controls::GetDriveThrottle()*driveStick->GetX();
}
double Controls::GetDriveY()
{
	return isAutonomous?autoDriver->GetDriveY():Controls::GetDriveThrottle()*driveStick->GetY();
}
double Controls::GetDriveR()
{
	return isAutonomous?autoDriver->GetDriveR():Controls::GetDriveThrottle()*driveStick->GetTwist();
}
double Controls::GetDriveThrottle()
{
	return (driveStick->GetThrottle+1)/2;
}