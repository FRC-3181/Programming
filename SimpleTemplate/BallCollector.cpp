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
        buttonEnabled=true;
}
//down is one
void BallCollector::AutonomousCollect(double sPower,double rPower){
  m_spinL->Set(-sPower*SPIN_SPEED);
  m_spinR->Set(sPower*SPIN_SPEED);
  m_raise->Set(RAISE_SPEED*rPower);
  Wait(0.3);
  while(ls->Get()){
      Wait(0.05);
  }
  while(!ls->Get()){
        Wait(0.05);
    }
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
        if(stick->GetRawButton(5)) m_raise->Set(-RAISE_SPEED);
        else switch(state){
            case UP:
              buttonEnabled=buttonEnabled||!stick->GetRawButton(4);
              buttonState=buttonState||(buttonEnabled&&stick->GetRawButton(4));
              m_raise->Set(buttonState?RAISE_SPEED:0);
              if(!ls->Get()&&buttonState){
                  state=LOWERING;
                  buttonState=false;
              }
            break;
            case LOWERING:
              buttonEnabled=buttonEnabled||!stick->GetRawButton(4);
              buttonState=false;
              m_raise->Set(RAISE_SPEED);
              if(ls->Get())
                {
                  state=DOWN;
                  buttonEnabled=!stick->GetRawButton(4);
                  
                }
            break;
            case DOWN:
              buttonEnabled=buttonEnabled||!stick->GetRawButton(4);
              buttonState=buttonState||(buttonEnabled&&stick->GetRawButton(4));
              m_raise->Set(buttonState?-RAISE_SPEED:0);
              if(!ls->Get()&&buttonState)
                {
                  state=RAISING;
                  buttonState=false;
                }
            break;
            case RAISING:
              m_raise->Set(-RAISE_SPEED);
              if(ls->Get())
                {
                  state=UP;
                  buttonEnabled=!stick->GetRawButton(4);
                }
            break;
        }

}
