#include "BallCollector.h"
#include "Hardware.h"
#include <math.h>

const double SPIN_SPEED=0.35;
const double RAISE_SPEED=1;


BallCollector::BallCollector(SpeedController* spinL, SpeedController* spinR, SpeedController* raise,
    DigitalInput* limit, Joystick *joystick)
{
        m_spinL = spinL;
        m_spinR = spinR;
        m_raise = raise;
        ls=limit;
        stick=joystick;
        state=UP;
        buttonState=false;
}
//down is one
void BallCollector::AutonomousCollect(double sPower,double rPower){
  m_spinL->Set(-sPower*SPIN_SPEED);
  m_spinR->Set(sPower*SPIN_SPEED);
  m_raise->Set(RAISE_SPEED*rPower);
  while(ls->Get()){
      Wait(0.05);
      Hardware::RobotLights->SetUnderGlow(UnderGlow::OFF,false);
  }
  while(!ls->Get()){
        Wait(0.05);
        Hardware::RobotLights->SetUnderGlow(UnderGlow::WHITE,false);
    }
  Hardware::RobotLights->SetUnderGlow(UnderGlow::GREEN,false);
  m_spinR->Set(0);
  m_spinL->Set(0);
  m_raise->Set(0);
  state=rPower>=0?DOWN:UP;
}
bool BallCollector::OKToShoot(){
  if(state==DOWN){
      return true;
  }
  else{
      m_raise->Set(RAISE_SPEED);
  }
}
void BallCollector::Collect()//Pick up the ball
{
        //Set Spinner Speed
        double spinDir = stick->GetRawButton(2)?1:(stick->GetRawButton(3)?-1:0);
        m_spinL->Set(-SPIN_SPEED * spinDir);
        m_spinR->Set(SPIN_SPEED * spinDir);
        //Set raise/lower speed
        switch(state){
            case UP:
              buttonState=buttonState||(stick->GetRawButton(4));
              m_raise->Set(buttonState?RAISE_SPEED:0);
              if(!ls->Get()&&buttonState){
                  state=LOWERING;
                  buttonState=false;
              }
            break;
            case LOWERING:
              buttonState=false;
              m_raise->Set(RAISE_SPEED);
              if(ls->Get())
                {
                  state=DOWN;                  
                }
            break;
            case DOWN:
              buttonState=buttonState||(stick->GetRawButton(4));
              m_raise->Set(buttonState?-RAISE_SPEED:0);
              if(buttonState)
                {
                  state=RAISING;
                  raiseTime=0;
                  buttonState=false;
                }
            break;
            case RAISING:
              m_raise->Set(-RAISE_SPEED);
              if(raiseTime>0.5)
                {
                  state=UP;
                }
            break;
        }

}
