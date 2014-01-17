#include "Controls.h"

Joystick *Controls::driveStick=NULL;
Joystick *Controls::auxStick=NULL;
bool Controls::isAutonomous=false;
bool Controls::isAiming=false;

AutonomousDriver *Controls::autoDriver=NULL;

const int trussButton=0;
const int targetButton=0;
const int aimButton=0;


void Controls::Init()
{
	driveStick=new Joystick(1);
	auxStick=new Joystick(2);
	isAutonomous=true;
	autoDriver=new AutonomousDriver();
}
double Controls::GetDriveX()
{
	return isAutonomous?autoDriver->GetDriveX():GetDriveThrottle()*driveStick->GetX();
}
double Controls::GetDriveY()
{
	return isAutonomous?autoDriver->GetDriveY():GetDriveThrottle()*driveStick->GetY();
}
double Controls::GetDriveR()
{
	return isAutonomous?autoDriver->GetDriveR():GetDriveThrottle()*driveStick->GetTwist();
}
double Controls::GetDriveThrottle()
{
	return (driveStick->GetThrottle+1)/2;
}
bool Controls::GetShootForTarget()
{
	return isAutonomous?autoDriver->GetShoot():auxStick->GetRawButton(targetButton);
}
bool Controls::GetShootOverTruss()
{
	return auxStick->GetRawButton(trussButton);
}
bool Controls::GetAiming()
{
	if(isAiming)return true;
	if(isAutonomous?autoDriver->ShouldStartAiming():auxStick->GetRawButton(aimButton)){
		isAiming=YES;
		return false;
	}
	return false;
}
void Controls::EndAiming()
{
	isAiming=false;
}

























