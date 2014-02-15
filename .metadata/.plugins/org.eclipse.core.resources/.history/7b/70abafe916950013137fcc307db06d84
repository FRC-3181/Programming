#include "Shooter.h"
#include "Controls.h"
#include "Vision.h"

const double RECOVER_SPEED=-0.05;
const double WAIT_TIME=100;//Time for waiting at the top in ms

BallShooter::BallShooter(SpeedController *left,SpeedController *right,DigitalInput *upper, DigitalInput *lower)
{
		m_l=left;
		m_r=right;
		ls_l=lower;
		ls_u=upper;
		//shotSpeed=0;
	//	fireSpeed=0;
		//state=OFF;
		//waitTimer=new Timer();
	}
void BallShooter::Lower()	//Bring the shooter back dwon
{
	double shotSpeed=(ls_l->Get()?0.0:RECOVER_SPEED);
	m_l->Set(-shotSpeed);
	m_r->Set(shotSpeed);
	if(shotSpeed!=0)DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line2,"Shooter Lowering");
	DriverStationLCD::GetInstance()->UpdateLCD();

}
void BallShooter::ShootBall()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line2,"Shooter Activated");

	//Deterime speed required to hit target
	double fireSpeed=Vision::FindPower();
	//Move shooter up
	double shotSpeed=0.0;
	while(!ls_u->Get())//If we hit the top, stop
	{
		shotSpeed=shotSpeed>=fireSpeed?fireSpeed:shotSpeed+0.05;//Determine Ramped motor speed
		//Set motor speeds
		m_l->Set(-shotSpeed);
		m_r->Set(shotSpeed);
		Wait(0.01);//Let the motors adjust their speeds
	}
	//Stop Motors when we hit the top
	m_l->Set(0);
	m_r->Set(0);
	//Wait a bit so that the ball has time to leave
	for(int i=0;i<WAIT_TIME;++i)
	{
		Wait(0.001);
	}
}
