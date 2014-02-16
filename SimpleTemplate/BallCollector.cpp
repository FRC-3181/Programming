#include "BallCollector.h"
#include "Hardware.h"
#include <math.h>

const double RSPEED=0.35;
const double SSPEED=0.35;
BallCollector::BallCollector(SpeedController* spinL, SpeedController* spinR, SpeedController* raise,Joystick *joystick)
{
        m_spinL = spinL;
        m_spinR = spinR;
        m_raise = raise;
        stick=joystick;
}
double deadzone(double speed){
  if(speed<0.3)return 0;
  return speed;
}
void BallCollector::Collect()//Pick up the ball
{
        //Set Spinner Speed
        double spinDir = deadzone(stick->GetX());
        m_spinL->Set(-SSPEED * spinDir);
        m_spinR->Set(SSPEED * spinDir);
        //Set raise/lower speed
        m_raise->Set(RSPEED * deadzone(stick->GetY()));
}
