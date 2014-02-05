#include "BallCollector.h"
#include "Controls.h"
#include "Hardware.h"
#include <math.h>

const double rSpeed=1;
const double sSpeed=1;
BallCollector:BallCollector(SpeedController *spinL,SpeedController*spinR,SpeedController*raise){
	m_spinL=spinL;
	m_spinR=spinR;
	m_raise=raise;
}

void BallCollector::collect(){//Pick up the ball
	//Set Spinner Speed
	int spinDir=Controls::GetCollectorSpin()
	m_spinL->Set(-sSpeed*spinDir);
	m_spinR->Set(sSpeed*spinDir);
	//Set raise/lower speed
	m_raise->Set(rSpeed*Controls::GetCollectorRaise());
}
