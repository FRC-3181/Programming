#include "BallCollector.h"
#include "Controls.h"
#include "Hardware.h"
#include <math.h>

const double RSPEED=0.25;
const double SSPEED=0.25;
BallCollector::BallCollector(SpeedController* spinL, SpeedController* spinR, SpeedController* raise,DigitalInput *upper, DigitalInput *lower)
{
	m_spinL = spinL;
	m_spinR = spinR;
	m_raise = raise;
	ls_u=upper;
	ls_l=lower;
}

void BallCollector::Collect()//Pick up the ball
{
	//Set Spinner Speed
	int spinDir = Controls::GetCollectorSpin();
	m_spinL->Set(-SSPEED * spinDir);
	m_spinR->Set(SSPEED * spinDir);
	//Set raise/lower speed
	double speed= Controls::GetCollectorRaise();
	if(speed<0&&ls_l->Get())speed=0;
	else if(speed>0&&ls_u->Get())speed=0;
	m_raise->Set(RSPEED * speed);
}
