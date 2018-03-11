#pragma once

#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <iostream>
#include "IntakeSubsystem.h"
#include "ScorerSubsystem.h"
#include "LiftSubsystem.h"
#include "ChainBarSubsystem.h"
#include "CORERobotLib.h"
#include "DriveSubsystem.h"
#include "COREHardware/COREJoystick.h"
#include "COREFramework/CORERobot.h"


/************************* Motors *************************/
#define FRONT_RIGHT_STEER_PORT 11
#define FRONT_LEFT_STEER_PORT 12
#define BACK_RIGHT_STEER_PORT 13
#define BACK_LEFT_STEER_PORT 14
#define FRONT_RIGHT_DRIVE_PORT 15
#define FRONT_LEFT_DRIVE_PORT 16
#define BACK_RIGHT_DRIVE_PORT 17
#define BACK_LEFT_DRIVE_PORT 18
#define RIGHT_LIFT_MOTOR_PORT 19
#define LEFT_LIFT_MOTOR_PORT 20
#define LEFT_INTAKE_MOTOR_PORT 21
#define RIGHT_INTAKE_MOTOR_PORT 22
#define CHAINBAR_MOTOR_PORT 23
#define ROTATION_MOTOR_PORT 24

/************************* Solenoids *************************/
#define SCORER_IN_SOLENOID_PORT 0
#define SCORER_OUT_SOLENOID_PORT 1
#define RIGHT_INTAKE_IN_SOLENOID_PORT 2
#define RIGHT_INTAKE_OUT_SOLENOID_PORT 3
#define LEFT_INTAKE_IN_SOLENOID_PORT 4
#define LEFT_INTAKE_OUT_SOLENOID_PORT 5

/************************* Digital Inputs *************************/
#define LIFT_BOTTOM_LIMIT_SWITCH 0

using namespace CORE;
using namespace std;

class CORE2018: public CORERobot {
private:
    static CORE2018 *m_instance;

public:
	CORE2018();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void test() override;
    void testInit() override;

    static CORE2018* GetInstance();

	DriveSubsystem driveSubsystem;
    ChainBarSubsystem chainBarSubsystem;
	LiftSubsystem liftSubsystem;
	IntakeSubsystem intakeSystem;
	ScorerSubsystem scorerSubsystem;
    COREConstant<double> m_chainBarIntakeAngle, m_chainBarSwitchAngle, m_chainBarUpAngle;
};
