#pragma once
#include "ctre/Phoenix.h"
#include "wpilib.h"
#include "CORERobotLib.h"


class ScorerSubsystem {
public:
	ScorerSubsystem();
	void robotInit();
	void autonInit();
	void auton();
	void teleopInit();
	void teleop();
	void intakeCube();
	void outakeCube();
	//COREJoystick *m_scorerJoystick;

private:
	DoubleSolenoid m_frontLeftSolenoid, m_frontRightSolenoid, m_backRightSolenoid, m_backLeftSolenoid;
	bool m_intakeIsClosed = false;
};

