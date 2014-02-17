#include "BallShooter.h"
#include "Hardware.h"
//#include "Vision.h"
#include <math.h>

const double RECOVER_SPEED = -0.25;
const int PASS_RELEASE_ANGLE = 50;

const double WAIT_TIME = 100;//Time for waiting at the top in ms
const double SHOOT_SPEED = 1.0;

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
}
void BallShooter::Shoot(){
  if(stick->GetTrigger())
  {
      if(Hardware::Collector->OKToShoot())ShootBall(stick->GetRawButton(5));
  }
  else{
      Lower();
  }
  
}
void BallShooter::AutonomousShoot(RobotBase* robot){
  
  while (robot->IsAutonomous() && robot->IsEnabled()){
      DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Shooting");
      DriverStationLCD::GetInstance()->UpdateLCD();
      ShootBall(false);
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
    DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line2,"encoder: %i",enc->Get());
    DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line3,"encoder raw: %i",enc->GetRaw());

}
void BallShooter::ShootBall(bool passing) 
{
  if(finishedShot){
      double shotSpeed = (ls_l->Get() ? 0.0 : RECOVER_SPEED);
          m_l->Set(-shotSpeed);
          m_r->Set(shotSpeed);
         if(ls_l->Get()) DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Lowering");

          DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line2,"encoder: %i",enc->Get());
          DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line3,"encoder raw: %i",enc->GetRaw());
          return;
  }
    if(!previouslyShooting){
        //Deterime speed required to hit target
        int releaseAngle = passing?PASS_RELEASE_ANGLE:50;
        enc->Reset();
        enc->Start(); 
        previouslyShooting=true;
        finishedShot=false;
    }
    m_l->Set(-SHOOT_SPEED);
    m_r->Set(SHOOT_SPEED);
    DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line2,"encoder: %i",enc->Get());
    DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line3,"encoder raw: %i",enc->GetRaw());

    //
    if( ls_u->Get() /*|| enc->GetRaw()>=releaseAngle*/)//If we hit the top, stop
    {
      enc->Stop();
      finishedShot=true;
      //Stop Motors when we hit the top
      m_l->Set(0);
      m_r->Set(0);
    }
}
