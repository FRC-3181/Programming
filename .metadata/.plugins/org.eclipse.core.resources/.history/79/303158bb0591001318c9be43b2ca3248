#include "WPILib.h"
#ifndef __SHOOTER__
#define __SHOOTER__

enum shooterState { //stage in shooting the ball
	off = 0, //not shooting
	firing=1, //Releasing ball
	waiting=2, //Waiting while ball leaves
	recovering=3 //Moving shooter back down
};
class Shooter
{
public:
	Shooter(SpeedController *left,SpeedController *right,AnalogChannel *pot);//Initialize the shoooter
	void shoot();//determine if we need to shoot
private:
	//Fire information
	double fireSpeed;//target speed
	shooterState state; //shooting state
	//Controlling shots
	double shotSpeed;//Speed motors are currently at
	Timer *waitTimer; //Wait between release and recover
	//Hardware
	SpeedController *m_l, *m_r;//Motors for shooting
	AnalogChannel *potentiometer;//potentiometer for determining release point
};

#endif
