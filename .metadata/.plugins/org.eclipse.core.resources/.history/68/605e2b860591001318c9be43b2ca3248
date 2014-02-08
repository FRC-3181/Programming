#include "Shooter.h"
#include "Controls.h"
#include "Vision.h"

const double recoverSpeed=-0.5;
const double waitTime=0;
const double potRelease=1.0;
const double potReset=0.0;

Shooter::Shooter(SpeedController *left,SpeedController *right,AnalogChannel *pot){
	m_l=left;
	m_r=right;
	fireSpeed=0;
	potentiometer=pot;
	state=off;
	waitTimer=new Timer();
}

void Shooter::shoot()
{
	switch (state){
		case off:
			if(Controls::GetFireButton()){
				//Aim
				fireSpeed=Vision::FindPower();
				state=firing;
			}
			m_l->Set(0);//Turn left motor off
			m_r->Set(0);//Turn right motor off
			break;
		case firing:{
			if(potentiometer->GetValue()>=potRelease){//If we have hit the relase point
				shotSpeed=0;
				m_l->Set(0);//Turn left motor off
				m_r->Set(0);//Turn right motor off
				state=waiting;//we now need to wait  a bit
				//Start the timer
				waitTimer->Reset();
				waitTimer->Start();
			}
			else{
				if(shotSpeed>=fireSpeed){//If we are at top speed, stay there
					shotSpeed=fireSpeed;
				}
				else{
					shotSpeed+=0.05;//Ramp motor up a bit
				}
				//Set motor speeds
				m_l->Set(shotSpeed);
				m_r->Set(shotSpeed);
			}
		}break;
		case waiting:{
			if(waitTimer->HasPeriodPassed(waitTime)){//If we waited long enough
				waitTimer->Stop();
				state=recovering;//Enter the recovering state
			}
		break;
		case recovering:{
			if(potentiometer->GetValue()<=potReset){//If we have come all the way down
				shotSpeed=0;
				m_l->Set(0);//Turn left motor off
				m_r->Set(0);//Turn right motor off
				state=off; //we are done shooting
			}
			else{
				if(shotSpeed<=recoverSpeed){//If we are at top speed, stay there
					shotSpeed=recoverSpeed;
				}
				else{
					shotSpeed-=0.05;//Ramp motor up a bit
				}
				//Set motor speeds
				m_l->Set(shotSpeed);
				m_r->Set(shotSpeed);
			}
		}break;
		}
	}
}
