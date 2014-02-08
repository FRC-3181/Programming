#include "Hardware.h"


//Static Variable Declarations
DriveSystem* Hardware::driveSys=NULL;
Shooter* Hardware::shooter=NULL;
BallCollector* Hardware::collector=NULL;

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
	
	//Initialize motors and sensors
	DriveFR = new Talon(2);
	DriveBR = new Talon(3);
	DriveBL = new Talon(4);
	DriveFL = new Talon(1);
	ShooterLeft = new Talon(5);
	ShooterRight = new Talon(6);
	CollectorSpinL = new Victor(7);
	CollectorSpinR = new Victor(8);
	CollectorRaise = new Victor(9);
	DriveGyro = new Gyro(1);
	shotPot = new AnalogChannel(2);
	
	//Initialize subsystems
	driveSys=new DriveSystem(DriveFL,DriveFR,DriveBL,DriveBR,DriveGyro);
	shooter=new Shooter(ShooterLeft,ShooterRight,shotPot);
	collector=new BallCollector(CollectorSpinL,CollectorSpinR,CollectorRaise);
}