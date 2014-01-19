#include "Shooter.h"
#include "Controls.h"
#include "Hardware.h"
#include "DriveSystem.h"
#include <math.h>

const double targetSpeed=1;
const double trussSpeed=0.5;
const double recoverSpeed=-0.5;
const double waitTime=0;

Shooter::Shooter(){
	aState=notAimed;
	fState=off;
}

void Shooter::shoot()
{
	//Shooter Code goes here
		switch (aState) {
			case notAimed:{//Not Aiming, shoot over truss or aim are options
				if(Controls::IsTargetMode()){
					Controls::SetFireLED(false);
					if(fabs(DriveSystem::gyroAngle())<0.1745){//Aiming Mode and Robot pointed at target
						aState=aiming;
						//TODO: Start aiming the shooter
					}
				}
				else if(Controls::IsTrussMode()){
					Controls::SetFireLED(true);
					if(Controls::GetFireButton()){
						aState=trussShooting;
						fState=firing;
						Hardware::ShooterMotor->Set(0.05);
					}
				}
				else Controls::SetFireLED(false);
			}break;
			case aiming:{//Determining Distance to target
				if(!Controls::IsTargetMode()){
					aState=notAimed;
				}
			}break;
			case aimed:{//Ready to fire
				if(!Controls::IsTargetMode()){
					aState=notAimed;
				}
				else if(Controls::GetShootAtTarget()){
					aState=shooting;
					fState=firing;
					Hardware::ShooterMotor->Set(0.05);
				}
			}break;
			case shooting:
			case trussShooting:{//fire
				runShootMotor();
			}break;
		}
}
void Shooter::runShootMotor(){
	switch (fState){
		case firing:{
			bool hasHitRelease=false;//TODO: Use encoder to determine this
			if(hasHitRelease){
				Hardware::ShooterMotor->Set(0);
				fState=waiting;
				waitStart=0;//Replace with current time
			}
			else{
				double maxSpeed=((aState==shooting)?targetSpeed:trussSpeed);
				if(Hardware::ShooterMotor->Get()>=maxSpeed)Hardware::ShooterMotor->Set(maxSpeed);
				else Hardware::ShooterMotor->Set(Hardware::ShooterMotor->Get()+0.05);
			}
		}break;
		case waiting:{
			double time=0;//Replace with current time
			if(time-waitStart>waitTime){
				fState=recovering;
				if(aState==shooting)Controls::EndAiming();
			}
		}break;
		case recovering:{
			bool hasHitStop=false;//TODO: Use encoder to determine this
			if(hasHitStop){
				Hardware::ShooterMotor->Set(0);
				fState=off;
				aState=notAimed;
			}
			else{
				if(Hardware::ShooterMotor->Get()<=recoverSpeed)Hardware::ShooterMotor->Set(recoverSpeed);
				else Hardware::ShooterMotor->Set(Hardware::ShooterMotor->Get()-0.05);
			}
		}break;
		case off:
			Hardware::ShooterMotor->Set(0);
			break;
	}
	
}
/*
void startAiming(Shooter *shooter){
	//Place Holder for now
	//...
	//When done:
	//shooter->aimState=aimed
}*/
