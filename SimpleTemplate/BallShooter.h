#include "WPILib.h"
#ifndef __SHOOTER__
#define __SHOOTER__

class BallShooter
{
public:
        BallShooter(SpeedController *left,SpeedController *right,
            DigitalInput *upper, DigitalInput *lower,Encoder *encoder,
            Joystick *stick);//Initialize the shoooter
        //void Shoot();//determine if we need to shoot
        void Shoot();
        void AutonomousShoot(RobotBase* robot);

private:
        void ShootBall(bool passing);

        void Lower();
        //Hardware
        SpeedController *m_l, *m_r;//Motors for shooting
        DigitalInput *ls_l,*ls_u;//Limit Switches for determining stopping point
        Joystick* stick;
        Encoder *enc;
        bool previouslyShooting,finishedShot;
        int releaseAngle;
        int lastAngle;
};

#endif
