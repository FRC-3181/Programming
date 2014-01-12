#include "DriveSystem.h"
#include "Controls.h"
#include "Hardware.h"
#include <math.h>
void DriveSystem::drive(){
	//Get Control Values
	double x=Controls::GetDriveX();
	double y=Controls::GetDriveY();
	double r=Controls::GetDriveR();
	//Do Some Math
	double scale=fabs(x)+fabs(y)+fabs(r);
	scale=(scale>1)?1/scale:1;
	double fl=y-x-r;
	double fr=y+x+r;
	double bl=y+x-r;
	double br=y-x+r;
	//Set Motor Values
	Hardware::DriveFL->Set(scale*fl);
	Hardware::DriveFR->Set(scale*fr);
	Hardware::DriveBL->Set(scale*bl);
	Hardware::DriveBR->Set(scale*br);
}