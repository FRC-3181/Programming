#include "BallCollector.h"
#include "Controls.h"
#include "Hardware.h"
#include <math.h>

const double RSPEED=0.25;
const double SSPEED=0.25;
BallCollector::BallCollector(SpeedController* spinL, SpeedController* spinR, SpeedController* raise)
{
	m_spinL = spinL;
	m_spinR = spinR;
	m_raise = raise;

}

void BallCollector::Collect()//Pick up the ball
{
	//Set Spinner Speed
	double spinDir = Controls::GetCollectorSpin();
	m_spinL->Set(-SSPEED * spinDir);
	m_spinR->Set(SSPEED * spinDir);
	//Set raise/lower speed
	double speed= Controls::GetCollectorRaise();
	m_raise->Set(RSPEED * speed);
}
