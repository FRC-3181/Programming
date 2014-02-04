#include "Shooter.h"
#include "Controls.h"
#include "Hardware.h"
#include "DriveSystem.h"
#include <math.h>

const double targetSpeed=1;
const double trussSpeed=0.5;
const double recoverSpeed=-0.5;
const double waitTime=0;
const double potRelease=1.0;
const double potReset=0.0;

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
						shotSpeed=0.05;

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
					shotSpeed=0.05;
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
			if(Hardware::shotPot->Get()>=potRelease){//If we have hit the relase point
				shotSpeed=0;
				Hardware::ShooterLeft->Set(0);//Turn left motor off
				Hardware::ShooterRight->Set(0);//Turn right motor off
				fState=waiting;//we now need to wait  a bit
				//Start the timer
				waitTimer->Reset();
				waitTimer->Start();
			}
			else{
				double maxSpeed=((aState==shooting)?targetSpeed:trussSpeed);//Don't go to fast
				if(shotSpeed>=maxSpeed){//If we are at top speed, stay there
					shotSpeed=maxSpeed;
				}
				else{
					shotSpeed+=0.05;//Ramp motor up a bit
				}
				//Set motor speeds
				Hardware::ShooterLeft->Set(shotSpeed);
				Hardware::ShooterRight->Set(shotSpeed);
			}
		}break;
		case waiting:{
			if(waitTimer->HasPeriodPassed(waitTime)){//If we waited long enough
				waitTimer->Stop();
				fState=recovering;//Enter the recovering state
			}
		}break;
		case recovering:{
			if(Hardware::pot->Get()<=potReset){//If we have come all the way down
				shotSpeed=0;
				Hardware::ShooterLeft->Set(0);//Turn left motor off
				Hardware::ShooterRight->Set(0);//Turn right motor off
				fState=off; //we are done shooting
				aState=notAimed;
			}
			else{
				double maxSpeed=((aState==shooting)?targetSpeed:trussSpeed);//Don't go to fast
				if(shotSpeed>=maxSpeed){//If we are at top speed, stay there
					shotSpeed=maxSpeed;
				}
				else{
					shotSpeed+=0.05;//Ramp motor up a bit
				}
				//Set motor speeds
				Hardware::ShooterLeft->Set(shotSpeed);
				Hardware::ShooterRight->Set(shotSpeed);
			}
		}break;
		case off:
			Hardware::ShooterLeft->Set(0);//Turn left motor off
			Hardware::ShooterRight->Set(0);//Turn right motor off
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
