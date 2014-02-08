#include "Controls.h"

const double DRIVE_TIME=3000;
const double DRIVE_SPEED=0.5;

AutonomousDriver::AutonomousDriver()
{
	driveTimer=new Timer();
}
void AutonomousDriver::StartTimer(){//Start the timer
	driveTimer->Reset();
	driveTimer->Start();
}
double AutonomousDriver::GetDriveY()//Get Y for driving
{
	return driveTimer->Get() <= DRIVE_TIME ? DRIVE_SPEED : 0;
}
bool AutonomousDriver::ShouldShoot(){ //Should we shoot
	return driveTimer->Get() > DRIVE_TIME;
}
