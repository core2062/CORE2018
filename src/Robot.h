#pragma once

#include "ctre/Phoenix.h"
//#include "IntakeSubsystem.h"
//#include "ScorerSubsystem.h"
//#include "ClimberSubsystem.h"
//#include "LiftSubsystem.h"
#include "CORERobotLib.h"
#include "DriveSubsystem.h"
#include "COREHardware/COREJoystick.h"

#define FRONT_RIGHT_STEER_PORT 11
#define FRONT_LEFT_STEER_PORT 12
#define BACK_RIGHT_STEER_PORT 13
#define BACK_LEFT_STEER_PORT 14
#define FRONT_RIGHT_DRIVE_PORT 15
#define FRONT_LEFT_DRIVE_PORT 16
#define BACK_RIGHT_DRIVE_PORT 17
#define BACK_LEFT_DRIVE_PORT 18

using namespace CORE;
using namespace std;

class CORE2018 : public CORERobot {
public:
	CORE2018();/*
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
	void TestPeriodic();*/
	//COREJoystick m_operatorJoystick;
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	COREJoystick m_driverJoystick;
	COREJoystick m_operatorJoystick;

	DriveSubsystem driveSubsystem;
	//ClimberSubsystem climberSubsystem;
	//LiftSubsystem liftSubsystem;
	//IntakeSubsystem intakeSystem;
	//ScorerSubsystem scorerSubsystem;

};

extern CORE2018 * Robot;
