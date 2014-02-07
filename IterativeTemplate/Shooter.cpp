#include "Shooter.h"
#include "Controls.h"

const double targetSpeed=1;
const double trussSpeed=0.5;
const double recoverSpeed=-0.5;
const double waitTime=0;
const double potRelease=1.0;
const double potReset=0.0;

Shooter::Shooter(SpeedController *left,SpeedController *right,AnalogChannel *pot){
	m_l=left;
	m_r=right;
	potentiometer=pot;
	state=off;
	waitTimer=new Timer();
}

void Shooter::shoot()
{
	switch (state){
		case off:
			if(Controls::GetFireButton()){
				//Start Aiming
				state=aiming;
			}
			m_l->Set(0);//Turn left motor off
			m_r->Set(0);//Turn right motor off
			break;
		case aiming:
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
				double maxSpeed=(trussShooting?trussSpeed:targetSpeed);//Don't go to fast
				if(shotSpeed>=maxSpeed){//If we are at top speed, stay there
					shotSpeed=maxSpeed;
				}
				else{
					shotSpeed+=0.05;//Ramp motor up a bit
				}
				//Set motor speeds
				m_l->Set(shotSpeed);
				m_r->Set(shotSpeed);
			}
		}break;
		case waiting:
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
				double maxSpeed=(trussShooting?trussSpeed:targetSpeed);//Don't go to fast
				if(shotSpeed>=maxSpeed){//If we are at top speed, stay there
					shotSpeed=maxSpeed;
				}
				else{
					shotSpeed+=0.05;//Ramp motor up a bit
				}
				//Set motor speeds
				m_l->Set(shotSpeed);
				m_r->Set(shotSpeed);
			}
		}break;
	}
	
}
