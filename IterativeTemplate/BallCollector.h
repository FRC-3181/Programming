#include "WPILib.h"
#ifndef __COLLECTOR__
#define __COLLECTOR__

enum collectState { //stage in executing a shot
	off = 0, //not shooting
	lowering=1, //Releasing ball
	waiting=2, //Waiting while ball leaves
	raising=3, //Moving shooter back down
	finishing=4;
};
class BallCollector
{
public:
	BallCollector();//Initialize the shoooter
	void collect();//determine if we need to shoot
private:
	Timer	waitTimer; //time when we released the ball
	collectState state; //Aiming state
};

#endif
