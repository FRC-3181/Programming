#include "WPILib.h"

#ifndef __UGLOW__
#define __UGLOW__

class UnderGlow{
  public:

  enum Color{
    OFF=0,
    BLUE=1,
    GREEN=2,
    CYAN=3,
    RED=4,
    MAGENTA=5,
    YELLOW=6,
    WHITE=7
  };

        UnderGlow(int r,int g,int b);
        ~UnderGlow();
        void SetUnderGlow(Color color);
        
private:
        Solenoid *red, *green, *blue;
        
};

#endif
