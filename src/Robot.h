#pragma once

#include "CORERobotLib.h"
#include "ctre/Phoenix.h"
#include "IntakeSubsystem.h"
#include "ScorerSubsystem.h"
#include "ClimberSubsystem.h"
#include "LiftSubsystem.h"
#include "CORERobot.h"

#define RIGHT_FRONT_STEER_MOTOR_PORT 1
#define LEFT_FRONT_STEER_MOTOR_PORT 2
#define RIGHT_BACK_STEER_MOTOR_PORT 3
#define LEFT_BACK_STEER_MOTOR_PORT 4
#define RIGHT_FRONT_DRIVE_MOTOR_PORT 5
#define RIGHT_BACK_DRIVE_MOTOR_PORT  6
#define LEFT_FRONT_DRIVE_MOTOR_PORT 7
#define LEFT_BACK_DRIVE_MOTOR_PORT 8

//DriveSubsystem  driveSubsysetm;
ClimberSubsystem climberSubsystem;
LiftSubsystem liftSubsystem;
IntakeSubsystem intakeSystem;
ScorerSubsystem scorerSubsystem;


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

};
