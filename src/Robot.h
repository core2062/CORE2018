#pragma once

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include <iostream>
//#include "IntakeSubsystem.h"
//#include "ScorerSubsystem.h"
#include "LiftSubsystem.h"
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
#define RIGHT_LIFT_MOTOR_PORT 19
#define LEFT_LIFT_MOTOR_PORT 20

using namespace CORE;
using namespace std;

class CORE2018: public CORERobot {
public:
	CORE2018();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;

	DriveSubsystem driveSubsystem;
	LiftSubsystem liftSubsystem;
	//IntakeSubsystem intakeSystem;
	//ScorerSubsystem scorerSubsystem;

};
