#include "Controls.h"

const double driveTime=3000;
const double driveSpeed=0.5;

AutonomousDriver::AutonomousDriver()
{
	driveTimer=new Timer();
}
void startTimer(){//Start the timer
	driveTimer->Reset();
	driveTimer->Start();
}
double AutonomousDriver::GetDriveY()//Get Y for driving
{
	return driveTimer->Get()<=driveTime?driveSpeed:0;
}
bool AutonomousDriver::ShouldShoot(){ //Should we shoot
	return driveTime->Get()>driveTime;
} 