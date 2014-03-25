#include "BallShooter.h"
#include "Hardware.h"
//#include "Vision.h"
#include <math.h>

const double RECOVER_SPEED = 0.25;
const double SHOOT_SPEED = -1.0;

const int MAX_SHOOT_ANGLE=120;
const int MIN_SHOOT_ANGLE=55;
const int RELEASE_ANGLE_1 = 60;
const int RELEASE_ANGLE_2 = 70;
const int RELEASE_ANGLE_3 = 80;
const int RELEASE_ANGLE_4 = 90;
const int RELEASE_ANGLE_5 = 100;
const double DUMP_SPEED= 0.5;


BallShooter::BallShooter(SpeedController *left, SpeedController *right,
                DigitalInput *upper, DigitalInput *lower,Encoder* encoder,
                Joystick *joystick) {
        m_l = left;
        m_r = right;
        ls_l = lower;
        ls_u = upper;
        stick=joystick;
        enc=encoder;
        releaseAngle=0;
        previouslyShooting=false;
        finishedShot=false;
        triggerState=false;
}
void BallShooter::EncoderTest()
{
  DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line5,"Encoder Raw: %i",enc->GetRaw());

}
double BallShooter::ShootPower()
{
  return (1-stick->GetThrottle())/2.0;
}
void BallShooter::Shoot()
{
  DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line3,"Shooter Power: %f %%",100*ShootPower());
  triggerState=triggerState||(stick->GetTrigger()&&ls_l->Get());
  if(triggerState)
  {
    int angle=0;
    if(stick->GetRawButton(6))angle=RELEASE_ANGLE_1;
    else if(stick->GetRawButton(7))angle=RELEASE_ANGLE_2;
    else if(stick->GetRawButton(8))angle=RELEASE_ANGLE_3;
    else if(stick->GetRawButton(9))angle=RELEASE_ANGLE_4;
    else if(stick->GetRawButton(10))angle=RELEASE_ANGLE_5;
    else if(stick->GetRawButton(11))angle=150;

    ShootBall(stick->GetRawButton(11),angle);
  }
  else{
      Lower();
  }
  
}
void BallShooter::AutonomousShoot(RobotBase* robot){
  
  while (robot->IsAutonomous() && robot->IsEnabled()){
      DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Shooting");
      DriverStationLCD::GetInstance()->UpdateLCD();
      if(Hardware::Collector->OKToShoot())ShootBall(false,0);
      Wait(0.05);
  }
}
void BallShooter::Lower() //Bring the shooter back down
{
    previouslyShooting=false;
    finishedShot=false;
    double shotSpeed = (ls_l->Get() ? 0.0 : RECOVER_SPEED);
    m_l->Set(-shotSpeed);
    m_r->Set(shotSpeed);
}
void BallShooter::ShootBall(bool slow,int angle) 
{
  if(finishedShot){
      double shotSpeed = (ls_l->Get() ? 0.0 : RECOVER_SPEED);
          m_l->Set(-shotSpeed);
          m_r->Set(shotSpeed);
          return;
  }
    if(!previouslyShooting){
        //Deterime speed required to hit target
        releaseAngle = angle==0?MIN_SHOOT_ANGLE+(MAX_SHOOT_ANGLE-MIN_SHOOT_ANGLE)*ShootPower():angle;
        slowShot=slow;
        enc->Reset();
        enc->Start(); 
        previouslyShooting=true;
        finishedShot=false;
    }        
    m_l->Set(-(slowShot?DUMP_SPEED:SHOOT_SPEED));
    m_r->Set(slowShot?DUMP_SPEED:SHOOT_SPEED);

    //
    if( ls_u->Get() || enc->GetRaw()>=releaseAngle)//If we hit the top, stop
    {
      enc->Stop();
      finishedShot=true;
      triggerState=false;
      //Stop Motors when we hit the top
      m_l->Set(0);
      m_r->Set(0);
    }
}
