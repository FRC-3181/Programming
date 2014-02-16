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
        
        void UnderGlow::setUnderGlow(bool r,bool g,bool b){
                red->Set(r);
                green->Set(g);
                blue->Set(b);
        }
        /*Color Scheme:
         * off: FFF
         * Red: TFF
         * Green: FTF
         * Blue: FFT
         * Magenta: TFT
         * Yellow: TTF
         * Cyan: FTT
         * White: TTT
         */
