// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Drivetrain.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/JoystickDrive.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    leftTop = RobotMap::drivetrainLeftTop;
    leftBottom = RobotMap::drivetrainLeftBottom;
    rightTop = RobotMap::drivetrainRightTop;
    rightBottom = RobotMap::drivetrainRightBottom;
    robotDrive = RobotMap::drivetrainRobotDrive;
    gyroUseless = RobotMap::drivetrainGyroUseless;
    comp = RobotMap::drivetrainComp;
    spikeBrake = RobotMap::drivetrainSpikeBrake;
    brakeSol = RobotMap::drivetrainBrakeSol;
    ultra = RobotMap::drivetrainUltra;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    gyro = RobotMap::drivetrainGyro;
    //Spike.reset(new Relay(0));
    Spike.reset(new Relay(0));

    drive_x = 0;
    drive_y = 0;

    //create variables for autonomous
    power = 0.750;
    kP = -.030;
    AutoTime = 5.500;
    Delay = 0.000;
    turnAngle = -60;

    LightState = false;

    DriveStateBool = false;

    TowerPos = "R";

    pos = false;
}

void Drivetrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new JoystickDrive());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

//this is the autonoumous code as of now, drive straight over
void Drivetrain::AutoGyroDrive(double Speed, double Correction)
{
	double angle = gyro->GetAngle();
	double idealAngle = 0;
	robotDrive->Drive(Speed, (idealAngle- angle) * -Correction);
}

//these functions should return SmartDashboard values, not sure if they work
double Drivetrain::GetPower()
{
	power = SmartDashboard::GetNumber("Power", power);
	return power;
}

double Drivetrain::GetkP()
{
	kP = SmartDashboard::GetNumber("kP", kP);
	return kP;
}

double Drivetrain::GetAutoTime()
{
	AutoTime = SmartDashboard::GetNumber("AutoTime", AutoTime);
	return AutoTime;
}

double Drivetrain::GetDelay()
{
	Delay = SmartDashboard::GetNumber("Auto Delay", Delay);
	return Delay;
}

std::string Drivetrain::GetDirection()
{
	TowerPos = SmartDashboard::GetString("Tower is", TowerPos);
	return TowerPos;
}

double Drivetrain::TurnAngle()
{
	turnAngle = SmartDashboard::GetNumber("Turn Angle", turnAngle);
	return turnAngle;
}

//stop the drivetrain
void Drivetrain::Stop()
{
	robotDrive->Drive(0,0);
}

//joystick drive, developed by Nathan
void Drivetrain::JoyDrive(std::shared_ptr<Joystick> stick)
{
	drive_x = stick->GetX() /* * .75*/;
	drive_y = stick->GetY() /* * .75*/;
	leftTop->Set(pow(drive_x, 3) + pow(-drive_y, 3));
	leftBottom->Set(pow(drive_x, 3) + pow(-drive_y, 3));
	rightTop->Set(pow(drive_x, 3) + pow(drive_y, 3));
	rightBottom->Set(pow(drive_x, 3) + pow(drive_y, 3));
}

//show the gyro angle
double Drivetrain::DisplayAngle()
{
	return gyro->GetAngle();
}

//this is the driver auto drive, should drive the robot staright over defenses in teleop
void Drivetrain::ForwardJoyDrive(std::shared_ptr<Joystick> joy)
{
	double angle = gyro->GetAngle();
	double idealAngle = 0;
	drive_y = Robot::oi->getJoy()->GetY();
	double DriveVar = pow(-drive_y,3);
	robotDrive->Drive(DriveVar, (angle - idealAngle) * kP);
}

void Drivetrain::BackwardJoyDrive(std::shared_ptr<Joystick> joy)
{
	double angle = gyro->GetAngle();
	double idealAngle = 0;
	drive_y = Robot::oi->getJoy()->GetY();
	double DriveVar = pow(-drive_y,3);
	robotDrive->Drive(DriveVar, (angle - idealAngle) * -kP);
}

//this should stop the drivetrain, by using a double solenoid to brake onto platform
void Drivetrain::EndGame()
{
	//robotDrive->Drive(0,0);
	brakeSol->Set(DoubleSolenoid::kReverse);
}

void Drivetrain::NotEndGame()
{
	brakeSol->Set(DoubleSolenoid::kForward);
}

//turn on light using spike
void Drivetrain::Light()
{
	Spike->Set(Relay::Value::kForward);
	LightState = true;
}

//turn off light using spike
void Drivetrain::LightOff()
{
	Spike->Set(Relay::Value::kOff);
	LightState = false;
}

//reset gyro because dumb reasons and code complications
void Drivetrain::ResetGyro()
{
	gyro->Reset();
}

double Drivetrain::GetDistance()
{
	return ultra->GetAverageVoltage() * 9.766 * 12;
}

bool Drivetrain::DriveState()
{
	if(DriveStateBool == false)
	{
		DriveStateBool = true;
	}
	else
	{
		DriveStateBool = false;
	}
	return DriveStateBool;
}

void Drivetrain::BackwardsAuto(double Speed, double Correction)
{
	double angle = gyro->GetAngle();
	double idealAngle = 0;
	robotDrive->Drive(-Speed, (angle - idealAngle) * -Correction);
}

void Drivetrain::TurnFun(std::string Direction, double TurnAngle)
{
	if(Direction == "L")
	{
		robotDrive->TankDrive(-.3,.3);
		pos = true;
	}
	else if(Direction == "R")
	{
		//robotDrive->TankDrive(.6,-.6);

		double angle = gyro->GetAngle();
		if(TurnAngle > 0)
		{
			double angle = gyro->GetAngle();
			if(angle - TurnAngle >= 0)
			{
				robotDrive->TankDrive(0.000, 0.000);
				pos = true;
			}
			else
			{
				robotDrive->TankDrive(.6, -.6);
				pos = false;
			}
		}
		else if (TurnAngle < 0)
		{
			double angle = gyro->GetAngle();
			if(TurnAngle - angle >= 0)
			{
				robotDrive->TankDrive(0.000, 0.000);
				pos = true;
			}
			else
			{
				robotDrive->TankDrive(-.6, .6);
				pos = false;
			}
		}
	}
}
/*
	if(TurnAngle > 0)
	{
		TurnRight();
	}
	else
	{
		TurnLeft();
	}
	*/

bool Drivetrain::GetPos()
{
	return pos;
}
/*
void Drivetrain::TurnRight(std::string Direction, double TurnAngle)
{
	if(Direction == "L")
	{
		robotDrive->TankDrive(-.3,.3);
		pos = true;
	}
	else if(Direction == "R")
	{
		//robotDrive->TankDrive(.6,-.6);
		double angle = gyro->GetAngle();
		if(angle - TurnAngle >= 0)
		{
			robotDrive->TankDrive(0.000, 0.000);
			pos = true;
		}
		else
		{
			robotDrive->TankDrive(.6, -.6);
			pos = false;
		}
	}
	else
	{
		robotDrive->Drive(0,0);
		pos = true;
	}
}
*/