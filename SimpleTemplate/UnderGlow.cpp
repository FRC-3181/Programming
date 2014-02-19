#include "UnderGlow.h"


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
        void UnderGlow::SetUnderGlow(Color color)
        {
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
          if(!run)
            {
              LSDTimer->Stop();
            }
          else if (!isLSDMode){
              LSDTimer->Reset();
              LSDTimer->Start();
          }
                if(LSDTimer->HasPeriodPassed(waitTime))
                  {
                    Color color=OFF;
                    while(color!=currentColor)
                      {
                        color=Color(rand()%7+1);
                      }
                    SetUnderGlow(color);
                    waitTime=(rand()%101)/2000.0+0.05-0.005;
                    LSDTimer->Reset();
                    LSDTimer->Start();
                  }
                isLSDMode=run;
        }
