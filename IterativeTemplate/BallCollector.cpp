#include "BallCollector.h"
#include "Controls.h"
#include "Hardware.h"
#include <math.h>

const double rSpeed=1;
const double sSpeed=1;

void BallCollector::collect(){//Pick up the ball
	Hardware::CollectorSpinL->Set(-sSpeed*Controls::GetCollectorSpin());
	Hardware::CollectorSpinR->Set(sSpeed*Controls::GetCollectorSpin());
	Hardware::CollectorRaise->Set(rSpeedControls::GetCollectorRaise());
}
