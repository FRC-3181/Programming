#include "WPILib.h"
#ifndef __SHOOTER__
#define __SHOOTER__

enum shooterState { //stage in executing a shot
	off = 0, //not shooting
	aiming=1, //Aiming the ball
	firing=2, //Releasing ball
	waiting=3, //Waiting while ball leaves
	recovering=4 //Moving shooter back down
};
class Shooter
{
public:
	Shooter();//Initialize the shoooter
	void shoot();//determine if we need to shoot
	shooterState state; //shooting state
	bool trussShooting;//are we passing over the truss
private:
	Timer *waitTimer; //Wait between release and recover
	double shotSpeed;
};

#endif
