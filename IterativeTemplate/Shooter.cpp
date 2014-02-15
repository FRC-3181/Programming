#include "Shooter.h"
#include "Controls.h"
#include "Vision.h"

const double RECOVER_SPEED = -0.1;
const double WAIT_TIME = 100;//Time for waiting at the top in ms
const double SHOOT_SPEED = 1.0;

BallShooter::BallShooter(SpeedController *left, SpeedController *right,
		DigitalInput *upper, DigitalInput *lower) {
	m_l = left;
	m_r = right;
	ls_l = lower;
	ls_u = upper;
}
void BallShooter::Lower() //Bring the shooter back down
{
	double shotSpeed = (ls_l->Get() ? 0.0 : RECOVER_SPEED);
	m_l->Set(-shotSpeed);
	m_r->Set(shotSpeed);
}
void BallShooter::ShootBall() 
{
	//Deterime speed required to hit target
	double fireSpeed = Vision::FindPower();
	//Move shooter up
	m_l->Set(-SHOOT_SPEED);
	m_r->Set(SHOOT_SPEED);
	while (!ls_u->Get())//If we hit the top, stop
	{
		Wait(0.005);//Let the motors adjust their speeds
	}

	//Stop Motors when we hit the top
	m_l->Set(0);
	m_r->Set(0);
	//Wait a bit so that the ball has time to leave
	Wait(WAIT_TIME);
}
