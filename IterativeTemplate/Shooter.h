#include "WPILib.h"
#ifndef __SHOOTER__
#define __SHOOTER__

class BallShooter
{
public:
	BallShooter(SpeedController *left,SpeedController *right,DigitalInput *upper, DigitalInput *lower,Encoder *encoder);//Initialize the shoooter
	//void Shoot();//determine if we need to shoot
	void ShootBall(bool passing);//Throw the ball
	void Lower();

private:
	//Hardware
	SpeedController *m_l, *m_r;//Motors for shooting
	DigitalInput *ls_l,*ls_u;//Limit Switches for determining stopping point
	Encoder *enc;
	bool previouslyShooting;
	int releaseAngle;
};

#endif
