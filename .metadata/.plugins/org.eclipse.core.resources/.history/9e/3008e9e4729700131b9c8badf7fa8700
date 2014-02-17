#include "WPILib.h"
#ifndef __COLLECTOR__
#define __COLLECTOR__

class BallCollector
{
public:
        BallCollector(SpeedController* spinL, SpeedController* spinR, SpeedController* raise,
            DigitalInput* upperLimit, DigitalInput* lowerLimit, Joystick *joystick);
        void Collect();//determine if we need to collect
        void AutonomousCollect(double sPower,double rPower);
        bool OKToShoot();
private:
        SpeedController* m_spinL,* m_spinR,* m_raise;//Motors for spinning and raising
        DigitalInput* ls_d,*ls_u;
        Joystick* stick;
};

#endif
