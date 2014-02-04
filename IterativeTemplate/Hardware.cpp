#include "Hardware.h"


SpeedController* Hardware::DriveFL = NULL;
SpeedController* Hardware::DriveBL = NULL;
SpeedController* Hardware::DriveFR = NULL;
SpeedController* Hardware::DriveBR = NULL;
SpeedController* Hardware::ShooterLeft = NULL;
SpeedController* Hardware::ShooterRight = NULL;
SpeedController* Hardware::CollectorSpin = NULL;
SpeedController* Hardware::CollectorRaise = NULL;

Gyro *Hardware::DriveGyro = NULL;
AnalogPotentiometer * Hardware::shotPot = NULL;
AnalogPotentiometer * Hardware::collectPot = NULL;


void Hardware::Init()
{
	DriveFR = new Talon(2);
	DriveBR = new Talon(3);
	DriveBL = new Talon(4);
	DriveFL = new Talon(1);
	ShooterLeft = new Talon(7);
	ShooterRight = new Talon(8);
	CollectorSpin = new Victor(5);
	CollectorRaise = new Victor(6);

	DriveGyro = new Gyro(1);
	shotPot = new AnalogChannel(2);
	collectPot = new AnalogChannel(3);

}