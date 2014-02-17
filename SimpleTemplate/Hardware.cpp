#include "Hardware.h"


//Static Variable Declarations
DriveSystem* Hardware::DriveSys = NULL;
BallShooter* Hardware::Shooter = NULL;
BallCollector* Hardware::Collector = NULL;
UnderGlow* Hardware::RobotLights=NULL;


void Hardware::Init()
{
  Joystick* driveStick=new Joystick(1);

  Joystick* ballStick=new Joystick(2);

     //Drive System
        SpeedController*  driveFL = new Talon(4);
         SpeedController* driveFR = new Talon(3);
         SpeedController* driveBR = new Talon(1);
         SpeedController* driveBL = new Talon(2);
       Gyro* driveGyro = new Gyro(1);
        DriveSys = new DriveSystem(driveFL, driveFR, driveBL, driveBR, driveGyro,driveStick);


//Shooter
        SpeedController* shooterLeft = new Talon(7);
        SpeedController* shooterRight = new Talon(8);
        DigitalInput* upperLimit=new DigitalInput(1);
        DigitalInput* lowerLimit=new DigitalInput(2);
        uint32_t port1=3,port2=4;
        Encoder* shootEncoder = new Encoder(port1, port2, true, Encoder::k4X);//Change Port numbers
        shootEncoder->Reset();
        Shooter = new BallShooter(shooterLeft, shooterRight, upperLimit,lowerLimit,shootEncoder,ballStick);

        //Collector
        SpeedController* collectorSpinLeft = new Victor(5);
       SpeedController* collectorSpinRight = new Victor(6);
       SpeedController* collectorRaise = new Victor(9);
       DigitalInput* upperCollectLimit=new DigitalInput(5);
              DigitalInput* lowerCollectLimit=new DigitalInput(6);
       Collector = new BallCollector(collectorSpinLeft, collectorSpinRight, collectorRaise,upperCollectLimit,lowerCollectLimit, ballStick);
       
       
       //RobotLights=new UnderGlow(1,2,3);

}
