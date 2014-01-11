#include "Hardware.h"

SpeedController* Hardware::DriveFL = NULL;
SpeedController* Hardware::DriveBL = NULL;
SpeedController* Hardware::DriveFR = NULL;
SpeedController* Hardware::DriveBR = NULL;

void Hardware::Init()
{
	DriveFR = new Victor(1);
	DriveBR = new Victor(2);
	DriveBL = new Victor(3);
	DriveFL = new Victor(4);
}
