#include "Shooter.h"
#include "Controls.h"
#include "Vision.h"

const double RECOVER_SPEED=-0.5;
const double WAIT_TIME=0;
const double POT_RELEASE=1.0;
const double POT_RESET=0.0;

Shooter::Shooter(SpeedController *left,SpeedController *right,AnalogChannel *pot)
{
	m_l=left;
	m_r=right;
	fireSpeed=0;
	potentiometer=pot;
	state = OFF;
	waitTimer = new Timer();
}

void Shooter::Shoot()
{
	switch (state)
	{
		case OFF:
			if(Controls::GetFireButton())
			{
				//Aim
				fireSpeed=Vision::FindPower();
				state=FIRING;
			}
			m_l->Set(0);//Turn left motor off
			m_r->Set(0);//Turn right motor off
			break;
		case FIRING:{
			if(potentiometer->GetValue()>=POT_RELEASE)//If we have hit the relase point
			{
				shotSpeed=0;
				m_l->Set(0);//Turn left motor off
				m_r->Set(0);//Turn right motor off
				state=WAITING;//we now need to wait  a bit
				//Start the timer
				waitTimer->Reset();
				waitTimer->Start();
			}
			else{
				if(shotSpeed>=fireSpeed)//If we are at top speed, stay there
				{
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
		case WAITING:{
			if(waitTimer->HasPeriodPassed(WAIT_TIME))//If we waited long enough
			{
				waitTimer->Stop();
				state=RECOVERING;//Enter the recovering state
			}
		break;
		case RECOVERING:{
			if(potentiometer->GetValue()<=POT_RESET)//If we have come all the way down
			{
				shotSpeed=0;
				m_l->Set(0);//Turn left motor off
				m_r->Set(0);//Turn right motor off
				state = OFF; //we are done shooting
			}
			else{
				if(shotSpeed<=RECOVER_SPEED)//If we are at top speed, stay there
				{
					shotSpeed=RECOVER_SPEED;
				}
				else
				{
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
