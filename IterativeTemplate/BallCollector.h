#include "WPILib.h"
#ifndef __COLLECTOR__
#define __COLLECTOR__

class BallCollector
{
public:
	BallCollector(SpeedController *spinL,SpeedController*spinR,SpeedController*raise);
	void collect();//determine if we need to collect
private:
	SpeedController *m_spinR, *m_spinR, *m_raise;//Motors for spinning and raising
};

#endif
