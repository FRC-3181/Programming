#include "WPILib.h"
#ifndef __SHOOTER__
#define __SHOOTER__

enum shooterState { //stage in shooting the ball
	OFF = 0, //not shooting
	FIRING = 1, //Releasing ball
	WAITING = 2, //Waiting while ball leaves
	RECOVERING = 3 //Moving shooter back down
};
class Shooter
{
public:
	Shooter(SpeedController *left,SpeedController *right,DigitalInput *upper, DigitalInput *lower);//Initialize the shoooter
	void Shoot();//determine if we need to shoot
private:
	//Fire information
	double fireSpeed;//target speed
	shooterState state; //shooting state
	//Controlling shots
	double shotSpeed;//Speed motors are currently at
	Timer* waitTimer; //Wait between release and recover
	//Hardware
	SpeedController *m_l, *m_r;//Motors for shooting
	DigitalInput *ls_l,*ls_u;//Limit Switches for determining stopping point
};

#endif
