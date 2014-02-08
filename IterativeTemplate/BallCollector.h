#include "WPILib.h"
#ifndef __COLLECTOR__
#define __COLLECTOR__

class BallCollector
{
public:
	BallCollector(SpeedController* spinL, SpeedController* spinR, SpeedController* raise);
	void Collect();//determine if we need to collect
private:
	SpeedController* m_spinL,* m_spinR,* m_raise;//Motors for spinning and raising
};

#endif
