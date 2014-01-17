#include "Hardware.h"

SpeedController* Hardware::DriveFL = NULL;
SpeedController* Hardware::DriveBL = NULL;
SpeedController* Hardware::DriveFR = NULL;
SpeedController* Hardware::DriveBR = NULL;
SpeedController* Hardware::ShooterMotor = NULL;

void Hardware::Init()
{
	DriveFR = new Talon(1);
	DriveBR = new Talon(2);
	DriveBL = new Talon(3);
	DriveFL = new Talon(4);
	ShooterMotor = new Talon(5);
	//testing commit from github for windows
}
