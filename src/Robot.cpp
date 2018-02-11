/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "CORERobotLib.h"
#include "ctre/Phoenix.h"
#include "IntakeSubsystem.h"
#include "ScorerSubsystem.h"
#include "ClimberSubsystem.h"
#include "LiftSubsystem.h"
#include "CORERobotLib.h"
#include "DriveSubsystem.h"

#define FRONT_RIGHT_STEER_PORT 11
#define FRONT_LEFT_STEER_PORT 12
#define BACK_RIGHT_STEER_PORT 13
#define BACK_LEFT_STEER_PORT 14
#define FRONT_RIGHT_DRIVE_PORT 15
#define FRONT_LEFT_DRIVE_PORT 16
#define BACK_RIGHT_DRIVE_PORT 17
#define BACK_LEFT_DRIVE_PORT 18

class Robot : public CORERobot {
public:
	DriveSubsystem driveSubsystem;

	void RobotInit() override {

	}

	/*
	 * This autonomous (along with the chooser code above) shows how to
	 * select between different autonomous modes using the dashboard. The
	 * sendable chooser code works with the Java SmartDashboard. If you
	 * prefer the LabVIEW Dashboard, remove all of the chooser code and
	 * uncomment the GetString line to get the auto name from the text box
	 * below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to
	 * the if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as
	 * well.
	 */
	void AutonomousInit() override {

	}

	void AutonomousPeriodic() override{

	}
	void DisabledInit() override {

	}
	void TeleopInit() override{

	}
	void TestInit() override{

	}

	void RobotPeriodic() override{

	}

	void DisabledPeriodic() override{

	}

	void TeleopPeriodic() override{

	}

	void TestPeriodic() override{

	}

	void StartCompetition() override{

	}

private:

};

START_ROBOT_CLASS(Robot)
