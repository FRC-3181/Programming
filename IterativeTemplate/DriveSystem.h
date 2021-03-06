#include "WPILib.h"
#ifndef __DRIVE__
#define __DRIVE__

class DriveSystem
{
public:
	DriveSystem(SpeedController* frontLeft,SpeedController* frontRight,SpeedController* backLeft,SpeedController* backRight,Gyro* gyro);
	void Drive(); //Adjust the wheel values to whatever the controls request
private:
	SpeedController *m_fl, *m_fr, *m_bl, *m_br;
	Gyro* rotateGyro;
	double GyroAngle();//Deterimine the angle that we have turned
	static void RotateAxes(double &x, double &y, double rotationAngle);
	static void ScaleComponents(double &x, double &y, double &r);
};
#endif
