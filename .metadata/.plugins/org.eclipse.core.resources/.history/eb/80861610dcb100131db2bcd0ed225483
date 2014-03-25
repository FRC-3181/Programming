#include "Hardware.h"

#define VictorDrive

//Static Variable Declarations
DriveSystem* Hardware::DriveSys = NULL;
BallShooter* Hardware::Shooter = NULL;
BallCollector* Hardware::Collector = NULL;
UnderGlow* Hardware::RobotLights=NULL;
AnalogChannel* Hardware::RangeFinder=NULL;

void Hardware::Init()
{
  Joystick* driveStick=new Joystick(1);

  Joystick* ballStick=new Joystick(2);
#ifdef VictorDrive
SpeedController* driveFL=new Victor(1);
SpeedController* driveFR=new Victor(2);
SpeedController* driveBR=new Victor(3);
SpeedController* driveBL=new Victor(4);
#else
     //Drive System
        SpeedController*  driveFL = new Talon(1);
         SpeedController* driveFR = new Talon(2);
         SpeedController* driveBR = new Talon(3);
         SpeedController* driveBL = new Talon(4);
#endif
       Gyro* driveGyro = new Gyro(1);
        DriveSys = new DriveSystem(driveFL, driveFR, driveBL, driveBR, driveGyro,driveStick);


//Shooter
        SpeedController* shooterLeft = new Talon(7);
        SpeedController* shooterRight = new Talon(8);
        DigitalInput* upperLimit=new DigitalInput(1);
        DigitalInput* lowerLimit=new DigitalInput(2);
        uint32_t port1=3,port2=4;
        Encoder* shootEncoder = new Encoder(port1, port2, false, Encoder::k4X);//Change Port numbers
        shootEncoder->Reset();
        Shooter = new BallShooter(shooterLeft, shooterRight, upperLimit,lowerLimit,shootEncoder,ballStick);

        //Collector
        SpeedController* collectorSpinLeft = new Victor(5);
       SpeedController* collectorSpinRight = new Victor(6);
       SpeedController* collectorRaise = new Victor(10);
       DigitalInput* collectLimit=new DigitalInput(5);
       Collector = new BallCollector(collectorSpinLeft, collectorSpinRight, collectorRaise,collectLimit, ballStick);
     
       
       
       RangeFinder=new AnalogChannel(3);
       
       
       RobotLights=new UnderGlow(1,2);

}
