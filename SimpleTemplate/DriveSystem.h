#include "WPILib.h"
#ifndef __DRIVE__
#define __DRIVE__

class DriveSystem
{
public:
        DriveSystem(SpeedController* frontLeft,SpeedController* frontRight,
            SpeedController* backLeft,SpeedController* backRight,
            Gyro* gyro, Joystick *joy);
        void Drive(); //Adjust the wheel values to whatever the controls request
        void DriveForward(double speed, double time);
        double GyroAngle();//Deterimine the angle that we have turned
        Joystick* stick;


private:
        SpeedController *m_fl, *m_fr, *m_bl, *m_br;
        Gyro* rotateGyro;
        bool gyroState, buttonState;
        bool TurboMode();
        void ReadControls(double &x, double &y, double &r);
        void RotateAxes(double &x, double &y);
        void ScaleComponents(double &x, double &y, double &r);
};
#endif
