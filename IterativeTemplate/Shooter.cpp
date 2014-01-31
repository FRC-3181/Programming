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
	waitTimer=new Timer();
}

void Shooter::shoot()
{
	//Shooter Code goes here
		switch (aState) {
			case notAimed:{//Not Aiming, shoot over truss or aim are options
				if(Controls::IsTargetMode()){//If the controls are in target mode
					Controls::SetFireLED(false);//Turn of the LED
					if(fabs(DriveSystem::gyroAngle())<0.1745){//If we the robot  ispointed at target
						aState=aiming;//We are now in the aiming state
						//TODO: Start aiming the shooter
					}
				}
				else if(Controls::IsTrussMode()){//If the controls are in truss mode
					Controls::SetFireLED(true);//Turn the LED on
					if(Controls::GetFireButton()){//If the fire button is prressed
						aState=trussShooting;//We are in the truss shooting state
						fState=firing;//The firing state is releasing the ball
						Hardware::ShooterMotor->Set(0.05);//Start the motor
					}
				}
				else Controls::SetFireLED(false);//Turn the LED off
			}break;
			case aiming:{//Determining Distance to target
				if(!Controls::IsTargetMode()){//If we switched out of target mode
					aState=notAimed;//we are back to the not aiming state
				}
			}break;
			case aimed:{//Ready to fire
				if(!Controls::IsTargetMode()){//If we switched out of target mode
					aState=notAimed;//we are back to the not aiming state
				}
				else if(Controls::GetFireButton()){//If the button is pressed
					aState=shooting;//State is shooting at target
					fState=firing;//Fire state is releasing the ball
					Controls::SetFireLED(false);//Turn the LED off
					Hardware::ShooterMotor->Set(0.05);//Start the motor
				}
			}break;
			case shooting:
			case trussShooting:{
				runShootMotor();//Run the shot execution code
			}break;
		}
}
void Shooter::runShootMotor(){//Execute the shot
	switch (fState){
		case firing:{
			bool hasHitRelease=false;//Have we hit the release point?      TODO: Use encoder to determine this
			if(hasHitRelease){//If we have hit the relase point
				Hardware::ShooterMotor->Set(0);//Turn the motor off
				fState=waiting;//we now need to wait  a bit
				//Start the timer
				waitTimer->Reset();
				waitTimer->Start();
			}
			else{
				double maxSpeed=((aState==shooting)?targetSpeed:trussSpeed);//Don't go to fast
				if(Hardware::ShooterMotor->Get()>=maxSpeed)Hardware::ShooterMotor->Set(maxSpeed);//If we are at top speed, stay there
				else Hardware::ShooterMotor->Set(Hardware::ShooterMotor->Get()+0.05);//If not, go up a bit
			}
		}break;
		case waiting:{
			if(waitTimer->HasPeriodPassed(waitTime)){//If we waited long enough
				waitTimer->Stop();
				fState=recovering;//Enter the recovering state
			}
		}break;
		case recovering:{
			bool hasHitStop=false;//Have we come back down all the way?    TODO: Use encoder to determine this
			if(hasHitStop){//If we have come all the way down
				Hardware::ShooterMotor->Set(0);//Turn off the motor
				fState=off; //we are done shooting
				aState=notAimed;
			}
			else{
				//If we are not at top speed, increase the speed a bit. If we are, stay there
				if(Hardware::ShooterMotor->Get()<=recoverSpeed)Hardware::ShooterMotor->Set(recoverSpeed);
				else Hardware::ShooterMotor->Set(Hardware::ShooterMotor->Get()-0.05);
			}
		}break;
		case off:
			Hardware::ShooterMotor->Set(0);//Turn the motor off
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
