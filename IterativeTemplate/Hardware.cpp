#include "Hardware.h"


SpeedController* Hardware::DriveFL = NULL;
SpeedController* Hardware::DriveBL = NULL;
SpeedController* Hardware::DriveFR = NULL;
SpeedController* Hardware::DriveBR = NULL;
SpeedController* Hardware::ShooterLeft = NULL;
SpeedController* Hardware::ShooterRight = NULL;
SpeedController* Hardware::CollectorSpinL = NULL;
SpeedController* Hardware::CollectorSpinR = NULL;
SpeedController* Hardware::CollectorRaise = NULL;

Gyro *Hardware::DriveGyro = NULL;
AnalogChannel * Hardware::shotPot = NULL;


void Hardware::Init()
{
	DriveFR = new Talon(2);
	DriveBR = new Talon(3);
	DriveBL = new Talon(4);
	DriveFL = new Talon(1);
	ShooterLeft = new Talon(5);
	ShooterRight = new Talon(6);
	CollectorSpin = new Victor(7);
	CollectorSpin = new Victor(8);
	CollectorRaise = new Victor(9);

	DriveGyro = new Gyro(1);
	shotPot = new AnalogChannel(2);
}