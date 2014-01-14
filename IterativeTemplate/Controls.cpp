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
	return driveStick->GetX();
}
double Controls::GetDriveY()
{
	return driveStick->GetY();
}
double Controls::GetDriveR()
{
	return driveStick->GetTwist();
}