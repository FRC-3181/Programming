#include "WPILib.h"
#ifndef __SHOOTER__
#define __SHOOTER__

enum aimState {
	notAimed = 0,
	aiming = 1,
	aimed=2,
	shooting=3,
	trussShooting=4
};
enum fireState {
	off = 0,
	firing=1,
	waiting=2,
	recovering=3
};
class Shooter
{
public:
	Shooter();
	void shoot();
private:
	void runShootMotor();
	double	waitStart;
	aimState aState;
	fireState fState;
};

#endif
