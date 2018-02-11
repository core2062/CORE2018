/*#pragma once

#include "CORERobotLib.h"
#include "ctre/Phoenix.h"
#include "IntakeSubsystem.h"
#include "ScorerSubsystem.h"
#include "ClimberSubsystem.h"
#include "LiftSubsystem.h"
#include "CORERobotLib.h"
#include "DriveSubsystem.h"

#define FRONT_RIGHT_STEER_PORT 2
#define BACK_RIGHT_STEER_PORT 1
#define FRONT_LEFT_STEER_PORT 3
#define BACK_LEFT_STEER_PORT 4
#define FRONT_RIGHT_DRIVE_PORT 5
#define FRONT_LEFT_DRIVE_PORT  6
#define BACK_RIGHT_DRIVE_PORT 7
#define BACK_LEFT_DRIVE_PORT 8


class Robot : public CORERobot {
public:
	Robot();
	void StartCompetition();
	void RobotInit();
	void DisabledInit();
	void AutonomousInit();
	void TeleopInit();
	void TestInit();
	void RobotPeriodic();
	void DisabledPeriodic();
	void AutonomousPeriodic();
	void TeleopPeriodic();
	void TestPeriodic();
	COREJoystick m_operatorJoystick;
	COREJoystick m_driverJoystick;

	DriveSubsystem  driveSubsysetm;
	ClimberSubsystem climberSubsystem;
	LiftSubsystem liftSubsystem;
	IntakeSubsystem intakeSystem;
	//ScorerSubsystem scorerSubsystem;

};
*/
