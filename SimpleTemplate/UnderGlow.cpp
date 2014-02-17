#include "UnderGlow.h"


        UnderGlow::UnderGlow(int r,int g,int b){

               red=new Solenoid(r);
                green=new Solenoid(g);
                blue=new Solenoid(b);
        }
        UnderGlow::~UnderGlow(){
                delete red;
                delete green;
                delete blue;
        }
        
        void UnderGlow::SetUnderGlow(Color color){
                red->Set(color&RED==RED);
                green->Set(color&GREEN==GREEN);
               blue->Set(color&BLUE==BLUE);
        }
     
