#include "WPILib.h"
#ifndef __COLLECTOR__
#define __COLLECTOR__

class BallCollector
{
  enum collectorState{
    UP=0,
    LOWERING=1,
    DOWN=2,
    RAISING=3
  };
public:
        BallCollector(SpeedController* spinL, SpeedController* spinR, SpeedController* raise,
            DigitalInput* limit, Joystick *joystick);
        void Collect();//determine if we need to collect
        void AutonomousCollect(double sPower,double rPower);
        bool OKToShoot();
private:
        bool buttonState;
        double raiseTime;
        collectorState state;
        SpeedController* m_spinL,* m_spinR,* m_raise;//Motors for spinning and raising
        DigitalInput* ls;
        Joystick* stick;
};

#endif
