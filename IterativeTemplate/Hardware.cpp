#include "Hardware.h"

/*Reversable Speed Controller*/
ReversableSpeedController::ReversableSpeedController(speedControllerType controllerType,int channel,bool reversed){
	isReversed=reversed;
	switch (controllerType) {
		case victor:
			controller=new Victor(channel);
			break;
		case jaguar:
			controller=new Jaguar(channel);
			break;
		case talon:
			controller=new Talon(channel);
			break;
		default:
			break;
	}
}
void ReversableSpeedController::Set(float value){
	controller->Set((isReversed?-1:1)*value);
}
float ReversableSpeedController::Get(){
	return (isReversed?-1:1)*controller->Get();
}

/*Hardware*/
ReversableSpeedController* Hardware::DriveFL = NULL;
ReversableSpeedController* Hardware::DriveBL = NULL;
ReversableSpeedController* Hardware::DriveFR = NULL;
ReversableSpeedController* Hardware::DriveBR = NULL;
ReversableSpeedController* Hardware::ShooterMotor = NULL;
ReversableSpeedController* Hardware::CollectorSpin = NULL;
ReversableSpeedController* Hardware::CollectorRaise = NULL;

Gyro *Hardware::DriveGyro = NULL;
Encoder * Hardware::encoder = NULL;


void Hardware::Init()
{
	DriveFR = new ReversableSpeedController(talon,1,false);
	DriveBR = new ReversableSpeedController(talon,2,false);
	DriveBL = new ReversableSpeedController(talon,3,true);
	DriveFL = new ReversableSpeedController(talon,4,true);
	ShooterMotor = new ReversableSpeedController(talon,5,false);
	CollectorSpin = new ReversableSpeedController(talon,6,false);
	CollectorRaise = new ReversableSpeedController(talon,7,false);
	DriveGyro = new Gyro(1);
	encoder = new Encoder(1, 2);
	//testing commit from github for windows
}