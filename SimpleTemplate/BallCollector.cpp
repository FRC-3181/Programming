#include "BallCollector.h"
#include "Hardware.h"
#include <math.h>

const double RSPEED=0.25;
const double SSPEED=0.25;
BallCollector::BallCollector(SpeedController* spinL, SpeedController* spinR, SpeedController* raise,Joystick *joystick)
{
        m_spinL = spinL;
        m_spinR = spinR;
        m_raise = raise;
        stick=joystick;
}

void BallCollector::Collect()//Pick up the ball
{
        //Set Spinner Speed
        double spinDir = stick->GetX();
        m_spinL->Set(-SSPEED * spinDir);
        m_spinR->Set(SSPEED * spinDir);
        //Set raise/lower speed
        m_raise->Set(RSPEED * stick->GetY());
}
