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
	state=off;
	waitTimer=new Timer();
}

void Shooter::shoot()
{
	switch (state){
		case off:
			if(Controls::GetFireButton()){
				//Start Aiming
				state=Aiming;
			}
			Hardware::ShooterLeft->Set(0);//Turn left motor off
			Hardware::ShooterRight->Set(0);//Turn right motor off
			break;
		case Aiming:
			break;
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
				double maxSpeed=(trussShooting?trussSpeed:targetSpeed);//Don't go to fast
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
				double maxSpeed=(trussShooting?trussSpeed:targetSpeed);//Don't go to fast
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
	}
	
}
