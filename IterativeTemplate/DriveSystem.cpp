#include "DriveSystem.h"
#include "Controls.h"
#include "Hardware.h"
#include <math.h>

const double corSpeed=0.3;

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
	if(Controls::IsTargetMode()&&fabs(DriveSystem::gyroAngle())>=0.1745){
		r=-corSpeed*DriveSystem::gyroAngle();
		x=0;
	}
	//Rotate Axes
	double xTemp=x, yTemp=y, angle=DriveSystem::gyroAngle();
	x=xTemp*cos(angle)+yTemp*sin(angle);
	y=yTemp*cos(angle)-xTemp*sin(angle);
	//Do Some Math
	double scale=fabs(x)+fabs(y)+fabs(r);
	scale=(scale>1)?1/scale:1;
	double fl=y-x-r;
	double fr=y+x+r;
	double bl=y+x-r;
	double br=y-x+r;
	//Set Motor Values
	Hardware::DriveFL->Set(kFL*scale*fl);
	Hardware::DriveFR->Set(kFR*scale*fr);
	Hardware::DriveBL->Set(kBL*scale*bl);
	Hardware::DriveBR->Set(kBR*scale*br);
}
double DriveSystem::gyroAngle()
{
	double angle=Hardware::DriveGyro->GetAngle();
	while (angle>180) angle-=360;
	while (angle<-180) angle+=360;
	angle*=0.01745;//Convert from degrees to radians
	return angle;
}
