#include "DriveSystem.h"
#include "Controls.h"
#include "Hardware.h"
#include <math.h>

//Speed at which we
const double corSpeed=0.3;

//Constants to adjust the speeds of the motors based on resistance
const double kFL=-1;
const double kFR=1;
const double kBL=-1;
const double kBR=1;


void DriveSystem::drive()
{
	//Get Control Values
	double x=Controls::GetDriveX();
	double y=Controls::GetDriveY();
	double r=Controls::GetDriveR();
	//Rotate to Face target if aiming
	if(Controls::IsTargetMode()&&fabs(DriveSystem::gyroAngle())>=0.1745){//If we are in target mode and not close enough to forward
		r=-corSpeed*DriveSystem::gyroAngle();//Change the R value
		x=0;//If we are correcting we should not translate
		y=0;
	}
	//Rotate Axes
	double xTemp=x, yTemp=y, angle=DriveSystem::gyroAngle();//Get the angle for the gyro and copy the x and y values
	x=xTemp*cos(angle)+yTemp*sin(angle);//x=x0*cos(theta)+y0*sin(theta)
	y=yTemp*cos(angle)-xTemp*sin(angle);//y=y0*cos(theta)-x0*sin(theta)
	//Do Some Math to determine wheel values
	double scale=fabs(x)+fabs(y)+fabs(r);//Scale back wheels if the joystick values are to high
	scale=(scale>1)?1/scale:1;
	double fl=y+x-r;//front left likes to go Forward, left, and CW
	double fr=y-x+r;//Front right likes to go forward, right, and CCW
	double bl=y-x-r;//Back left likes to go Forward, right, and CW
	double br=y+x+r;//Back right likes to go Forward, left, and  CCW
	//Set Motor Values
	Hardware::DriveFL->Set(kFL*scale*fl);//Constant for Motor * scale for all motors * calculated value
	Hardware::DriveFR->Set(kFR*scale*fr);
	Hardware::DriveBL->Set(kBL*scale*bl);
	Hardware::DriveBR->Set(kBR*scale*br);
}
double DriveSystem::gyroAngle()//Get the angle we have turned
{
	double angle=Hardware::DriveGyro->GetAngle();//Read the gyro angle
	//Get it in desired range
	while (angle>180) angle-=360;
	while (angle<-180) angle+=360;
	angle*=0.01745;//Convert from degrees to radians
	return angle;
}
