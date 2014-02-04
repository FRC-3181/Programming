#include "Shooter.h"
#include "Controls.h"
#include "Hardware.h"
#include "DriveSystem.h"
#include <math.h>

const double upSpeed=0.5;
const double downSpeed=-0.5;
const double spinSpeed=0.5;
const double waitTime=0;
const double finishTime=0;
const double lowPot=0;
const double highPot=1;

BallCollector::BallCollector(){
	state=off;
	waitTimer=new Timer();
}

void BallCollector::collect(){//Pick up the ball
	switch (state){
		case off:
			if(Controls::GetCollectorButton()){
				Hardware::CollectorSpin->Set(1);
				Hardware::CollectorRaise->Set(-0.05);
				state=lowering;
			}
			else if(Controls::GetRejectButton()){
				Hardware::CollectorSpin->Set(-1);
				Hardware::CollectorRaise->Set(-0.05);
				state=lowering;
			}
			else{
				//Turn the motors off
				Hardware::CollectorSpin->Set(0);
				Hardware::CollectorRaise->Set(0);
			}
			break;

		case lowering:{
			if(Hardware::collectPot->Get()<=lowPot){//If we have hit the relase point
				Hardware::CollectorRaise->Set(0);//Turn the motor off
				state=waiting;//we now need to wait  a bit
				//Start the timer
				waitTimer->Reset();
				waitTimer->Start();
			}
			else{
				if(Hardware::CollectorRaise->Get()<=downSpeed)Hardware::CollectorRaise->Set(downSpeed);//If we are at top speed, stay there
				else Hardware::CollectorRaise->Set(Hardware::CollectorRaise->Get()-0.05);//If not, go up a bit
			}
		}break;
		case waiting:{
			if(waitTimer->HasPeriodPassed(waitTime)){//If we waited long enough
				waitTimer->Stop();
				state=raising;//Enter the recovering state
			}
		}break;
		case raising:{
			if(Hardware::collectPot->Get()>=highPot){//If we have hit the relase point
				Hardware::CollectorRaise->Set(0);//Turn the motor off
				state=finishing;//we now need to wait  a bit
				//Start the timer
				waitTimer->Reset();
				waitTimer->Start();
			}
			else{
				if(Hardware::CollectorRaise->Get()>=upSpeed)Hardware::CollectorRaise->Set(upSpeed);//If we are at top speed, stay there
				else Hardware::CollectorRaise->Set(Hardware::CollectorRaise->Get()+0.05);//If not, go up a bit
			}
		}break;
		case finishing:{
			if(waitTimer->HasPeriodPassed(waitTime)){//If we waited long enough
				waitTimer->Stop();
				Hardware::CollectorSpin->Set(0);
				state=off;//Enter the recovering state
			}
		}break;
	}
	
}
