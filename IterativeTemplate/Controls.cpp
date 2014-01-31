#include "Controls.h"

//Set up stuff
Joystick *Controls::driveStick=NULL;
DriverSationEnhancedIO *Controls::auxIO=NULL;
bool Controls::isAutonomous=false;
TargetMode Controls::tMode=0;

AutonomousDriver *Controls::autoDriver=NULL;

const int targetModePort=0; //Button for target mode
const int trussModePort=0; //button for truss mode
const int FireButtonPort=0; //Button to launch the ball
const int CollectButtonPort=0; //Button to launch the ball
const int LEDPort=0; //LED to light up button for launching

void Controls::Init()
{
	driveStick=new Joystick(1); //Drive Joystick
	auxIO=DriverSation::GetInstance->GetEnhancedIO(); //Cypress Module
	isAutonomous=true;
	autoDriver=new AutonomousDriver();
}
//Drive Stuff
double Controls::GetDriveX()//X value for driving (side to side)
{
	//If autonomous, ask the Autonomous driver. Otherwise get the throttle-adjusted X value from the Joystick
	return isAutonomous?autoDriver->GetDriveX():GetDriveThrottle()*driveStick->GetX();
}
double Controls::GetDriveY() //Y value for driving (forward and backward)
{
	//If we are aiming, there should be no Y value
	//If autonomous, ask the Autonomous driver. Otherwise get the throttle-adjusted Y value from the Joystick
	return isAiming?0:(isAutonomous?autoDriver->GetDriveY():GetDriveThrottle()*driveStick->GetY());
}
double Controls::GetDriveR()//Rotation value for driving
{
	//If we are aiming, there should be no Rotation value
	//If autonomous, ask the Autonomous driver. Otherwise get the throttle-adjusted Rotation value from the Joystick
	return isAiming?0:(isAutonomous?autoDriver->GetDriveR():GetDriveThrottle()*driveStick->GetTwist());
}
double Controls::GetGyroReset()
{
	return driveStick->GetRawButton(6);
}
double Controls::GetDriveThrottle()//Throttle for drivng
{
	//Get Throttle returns -1 for full up and 1 for full down, convert this to 1 for full up and 0 for full down
	return (1-driveStick->GetThrottle)/2;
}
//Shooter and collector
bool Controls::IsTargetMode()//Has the driver activated target mode
{
	//If we are in autonomous, ask the auto driver if we should prepare to fire
	//If we are in Teleop, check the input
	return isAutonomous?autoDriver->ShouldStartAiming():auxIO->GetDigital(targetModePort);
}
bool Controls::IsTrussMode()//Has the driver activated truss mode
{
	//check the input
	return auxIO->GetDigital(trussModePort);
}
bool Controls::GetFireButton()//Has the driver pressed the fire button
{
	//If we have are in Autonomous, ask the auto driver if we should fire
	//If we are in teleop, check the fire button
	return isAutonomous?autoDriver->GetShoot():auxIO->GetDigital(FireButtonPort);
}
bool Controls::GetCollectorButton()//Has the driver pressed the collect button
{
	//check the button
	return auxIO->GetDigital(CollectButtonPort);
}
void Controls::SetFireLED(bool val)//Turn the Fire button LED on or off
{
	auxIO->SetDigitalOutput(LEDPort,val);
}

























