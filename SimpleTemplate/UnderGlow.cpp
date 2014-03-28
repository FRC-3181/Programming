#include "UnderGlow.h"
const int minLSDMillis=1000;
const int maxLSDMillis=1500;

        UnderGlow::UnderGlow(int port1,int port2)
        {

              alliance=new Relay(port1);
              turbo=new Relay(port2);
              LSDTimer=new Timer();
              isLSDMode=false;
        }
        UnderGlow::~UnderGlow()
        {
                delete alliance;        
                delete turbo;
        }
        void UnderGlow::SetUnderGlow(Color color, bool LSD)
        {
          if(LSD!=isLSDMode)return;
          currentColor=color;
          if((color&RED)==RED)
                {
                    alliance->Set((color&BLUE)==BLUE?Relay::kOff:Relay::kForward);
                }
                else
                  {
                    alliance->Set((color&BLUE)==BLUE?Relay::kReverse:Relay::kOn);

                  }
                turbo->Set(((color&GREEN)==GREEN)?Relay::kForward:Relay::kOn);
        }
        void UnderGlow::LSDSimulator(bool run)
        {      
          return;
          if(!run)
            {
              LSDTimer->Stop();
            }
          else if (!isLSDMode){
              LSDTimer->Reset();
              LSDTimer->Start();
              waitTime=0;
          }
          if(LSDTimer->HasPeriodPassed(waitTime))
          {

              Color color=OFF;
             do{
                   color=Color(rand()%7+1);
              }
              while(color==currentColor&&DriverStation::GetInstance()->IsEnabled());
              SetUnderGlow(color,true);
              waitTime=(rand()%(maxLSDMillis-minLSDMillis)+minLSDMillis)/1000;
              LSDTimer->Reset();
              LSDTimer->Start();
          }
          isLSDMode=run;
          DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line4,isLSDMode?"LSD ON":"LSD OFF");
        }
