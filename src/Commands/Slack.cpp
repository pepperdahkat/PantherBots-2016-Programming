
// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Slack.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

Slack::Slack(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::catapult.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void Slack::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Slack::Execute() {
	Robot::catapult->Forward();
	// Calls for Robot::catapult to be propelled forward
}

// Make this return true when this Command no longer needs to run execute()
bool Slack::IsFinished() {
    //return Robot::catapult->GetAverageVoltage() < .699;
    return false;
	// If forward motion is complete, returns that information
}

// Called once after isFinished returns true
void Slack::End() {
	Robot::catapult->STOP();
	// If isFinished returns true, stops forward motion of catapult
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Slack::Interrupted() {
	End();
	// If forward motion is interrupted by something, stops the motion altogether
}
