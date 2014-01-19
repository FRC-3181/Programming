#include "Controls.h"

Joystick *Controls::driveStick=NULL;
DriverSationEnhancedIO *Controls::auxIO=NULL;
bool Controls::isAutonomous=false;
TargetMode Controls::tMode=0;

AutonomousDriver *Controls::autoDriver=NULL;

const int targetModePort=0;
const int trussModePort=0;
const int FireButtonPort=0;
const int LEDPort=0;

void Controls::Init()
{
	driveStick=new Joystick(1);
	auxIO=DriverSation::GetInstance->GetEnhancedIO();
	isAutonomous=true;
	autoDriver=new AutonomousDriver();
}
//Drive Stuff
double Controls::GetDriveX()
{
	return isAutonomous?autoDriver->GetDriveX():GetDriveThrottle()*driveStick->GetX();
}
double Controls::GetDriveY()
{
	return isAiming?0:(isAutonomous?autoDriver->GetDriveY():GetDriveThrottle()*driveStick->GetY());
}
double Controls::GetDriveR()
{
	return isAiming?0:(isAutonomous?autoDriver->GetDriveR():GetDriveThrottle()*driveStick->GetTwist());
}
double Controls::GetDriveThrottle()
{
	return (driveStick->GetThrottle+1)/2;
}
//Shooter
bool Controls::IsTargetMode()
{
	return isAutonomous?autoDriver->ShouldStartAiming():auxIO->GetDigital(targetModePort);
}
bool Controls::IsTrussMode()
{
	return auxIO->GetDigital(trussModePort);
}
bool Controls::GetFireButton()
{
	return isAutonomous?autoDriver->GetShoot():auxIO->GetDigital(FireButtonPort);

}
void Controls::SetFireLED(bool val)
{
	auxIO->SetDigitalOutput(LEDPort,val);
}

























