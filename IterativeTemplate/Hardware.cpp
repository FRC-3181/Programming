#include "Hardware.h"


//Static Variable Declarations
DriveSystem* Hardware::DriveSys = NULL;
BallShooter* Hardware::Shooter = NULL;
BallCollector* Hardware::Collector = NULL;

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
DigitalInput* Hardware::UpperLimit=NULL;
DigitalInput* Hardware::LowerLimit=NULL;

/*Wiring Problems:
 * Drive Front Left (Talon 4)
 * Shooter Left (Talon 7)
 * Shooter Right (Talon 8)
 * 
 */

void Hardware::Init()
{
	//Drive System
	//DriveFL = new Talon(4);
//	DriveFR = new Talon(3);
//	DriveBR = new Talon(1);
//	DriveBL = new Talon(2);
//	DriveGyro = new Gyro(1);
	//DriveSys = new DriveSystem(DriveFL, DriveFR, DriveBL, DriveBR, DriveGyro);


//Shooter
	ShooterLeft = new Talon(7);
	ShooterRight = new Talon(8);
	UpperLimit=new DigitalInput(1);
	LowerLimit=new DigitalInput(2);
	Shooter = new BallShooter(ShooterLeft, ShooterRight, UpperLimit,LowerLimit);
	return;

	CollectorSpinL = new Victor(5);
	CollectorSpinR = new Victor(6);
	CollectorRaise = new Victor(9);
	Collector = new BallCollector(CollectorSpinL, CollectorSpinR, CollectorRaise);
	
	//
//	
}
