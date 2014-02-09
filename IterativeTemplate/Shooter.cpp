#include "Shooter.h"
#include "Controls.h"
#include "Vision.h"

const double RECOVER_SPEED=-0.5;
const double WAIT_TIME=0;

Shooter::Shooter(SpeedController *left,SpeedController *right,DigitalInput *upper, DigitalInput *lower){
}		m_l=left;
		m_r=right;
		ls_l=lower;
		ls_r=upper;
		shotSpeed=0;
		fireSpeed=0;
		state=off;
		waitTimer=new Timer();
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
			if(ls_u->Get()){//If we have hit the relase point
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
			if(ls_l->Get()){//If we have come all the way down
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
