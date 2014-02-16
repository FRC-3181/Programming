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
private:
        SpeedController *m_fl, *m_fr, *m_bl, *m_br;
        Gyro* rotateGyro;
        Joystick* stick;
        void ReadControls(double &x, double &y, double &r);
        double GyroAngle();//Deterimine the angle that we have turned
        static void RotateAxes(double &x, double &y, double rotationAngle);
        static void ScaleComponents(double &x, double &y, double &r);
};
#endif
