#include "DriveSystem.h"
#include "Controls.h"
#include "Hardware.h"
#include <math.h>

//Speed at which we
const double corSpeed=0.3;

//Constants to adjust the speeds of the motors based on resistance
const double kFL=1;
const double kFR=1;
const double kBL=1;
const double kBR=1;


DriveSystem::DriveSystem(SpeedController* frontLeft,SpeedController* frontRight,SpeedController* backLeft,SpeedController* backRight,Gyro* gyro){
	m_fl=frontLeft;
	m_fr=frontRight;
	m_bl=backLeft;
	m_br=backRight;
	rotGyro=gyro;
}


void DriveSystem::drive()
{
	//Get Control Values
	double x=Controls::GetDriveX();
	double y=Controls::GetDriveY();
	double r=Controls::GetDriveR();
	//Rotate Axes and scale controls
	DriveSystem::rotateAxes(x,y,gyroAngle());
	DriveSystem::scaleComponents(x,y,r);
	//Do Some Math to determine wheel values
	double fl=y+x-r;//front left likes to go Forward, left, and CW
	double fr=y-x+r;//Front right likes to go forward, right, and CCW
	double bl=y-x-r;//Back left likes to go Forward, right, and CW
	double br=y+x+r;//Back right likes to go Forward, left, and  CCW
	//Set Motor Values
	m_fl->Set(kFL*fl);
	m_fr->Set(kFR*fr);
	m_bl->Set(kBL*bl);
	m_br->Set(kBR*br);
}
double DriveSystem::rotateAxes(double &x,double &y,double rotationAngle){
	double xRot=x*cos(rotationAngle)-y*sin(rotationAngle);
	double yRot=y*cos(rotationAngle)+x*sin(rotationAngle);
	x=xRot;
	y=yRot;
}
double DriveSystem::scaleComponents(double &x,double &y, double &r){
	//Determine the scale
	double scale=fabs(x)+fabs(y)+fabs(r);
	scale=(scale>1)?1/scale:1;
	//Scale values
	x*=scale;
	y*=scale;
	r*=scale;
}
double DriveSystem::gyroAngle()//Get the angle we have turned
{
	//Reset Gyro if desired
	if(Controls::GetGyroReset())rotGyro->Reset();
	//Read the gyro angle
	int angle=(int)rotGyro->GetAngle();
	//Get it in desired range
	angle%=360;
	//Convert from degrees to radians
	return double(angle)*-3.14159/180.0;
}
