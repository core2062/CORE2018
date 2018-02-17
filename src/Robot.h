#pragma once

#include <wpilib.h>
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

class CORE2018: public frc::TimedRobot {
public:
	CORE2018();
	void RobotInit() override;
	void DisabledInit() override;
	void TeleopPeriodic() override;
	void AutonomousInit() override;
	void TeleopInit() override;
	void TestInit() override;
	void RobotPeriodic() override;
	void DisabledPeriodic() override;
	void AutonomousPeriodic() override;
	void TestPeriodic() override;

	~CORE2018();
	COREJoystick m_driverJoystick;
	COREJoystick m_operatorJoystick;
	DriveSubsystem driveSubsystem;
	//ClimberSubsystem climberSubsystem;
	//LiftSubsystem liftSubsystem;
	//IntakeSubsystem intakeSystem;
	//ScorerSubsystem scorerSubsystem;

};

extern CORE2018 * Robot;
