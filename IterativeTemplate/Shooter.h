#include "WPILib.h"
#ifndef __SHOOTER__
#define __SHOOTER__

enum aimState {//State that the shooter is in for aiming/waiting to shoot/shooting
	notAimed = 0, //Waiting to shoot over truss or begin aiming
	aiming = 1, //Determining distance to target
	aimed=2, //ready to shoot at target
	shooting=3, //shooting at target
	trussShooting=4 //Shooting over truss
};
enum fireState { //stage in executing a shot
	off = 0, //not shooting
	firing=1, //Releasing ball
	waiting=2, //Waiting while ball leaves
	recovering=3 //Moving shooter back down
};
class Shooter
{
public:
	Shooter();//Initialize the shoooter
	void shoot();//determine if we need to shoot
private:
	Timer *waitTimer; //Wait between release and recover
	void runShootMotor(); //execute a shot
	aimState aState; //Aiming state
	fireState fState; //shooting state
	double shotSpeed;
};

#endif
