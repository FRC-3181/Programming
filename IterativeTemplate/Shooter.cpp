#include "Shooter.h"
#include "Controls.h"
#include "Vision.h"

const double RECOVER_SPEED = -0.1;
const int PASS_RELEASE_ANGLE = 50;

const double WAIT_TIME = 100;//Time for waiting at the top in ms
const double SHOOT_SPEED = 1.0;

BallShooter::BallShooter(SpeedController *left, SpeedController *right,
		DigitalInput *upper, DigitalInput *lower,Encoder *encoder) {
	m_l = left;
	m_r = right;
	ls_l = lower;
	ls_u = upper;
	enc=encoder;
	releaseAngle=0;
	previouslyShooting=false;
}
void BallShooter::Lower() //Bring the shooter back down
{
    previouslyShooting=false;
    double shotSpeed = (ls_l->Get() ? 0.0 : RECOVER_SPEED);
    m_l->Set(-shotSpeed);
    m_r->Set(shotSpeed);
}
void BallShooter::ShootBall(bool passing) 
{
    if(!previouslyShooting){
        //Deterime speed required to hit target
        int releaseAngle = passing?PASS_RELEASE_ANGLE:Vision::FindAngle();
      //  enc->Reset();
      //  enc->Start(); 
        previouslyShooting=true;
    }
    m_l->Set(-SHOOT_SPEED);
    m_r->Set(SHOOT_SPEED);
    //|| enc->GetRaw()>=releaseAngle
    if( ls_u->Get()  )//If we hit the top, stop
    {
     // enc->Stop();
      //Stop Motors when we hit the top
      m_l->Set(0);
      m_r->Set(0);
    }
}
