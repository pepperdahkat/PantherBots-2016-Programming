// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutoSlack.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoSlack::AutoSlack(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::catapult.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoSlack::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoSlack::Execute() {
	Robot::catapult->Forward();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoSlack::IsFinished() {
    return Robot::catapult->GetAverageVoltage() < .544;
}

// Called once after isFinished returns true
void AutoSlack::End() {
	Robot::catapult->STOP();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoSlack::Interrupted() {
	End();
}