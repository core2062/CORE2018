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
	void rotateCube();
	void intakeCube();
	void outakeCube();

private:
	DoubleSolenoid m_frontLeftSolenoid, m_frontRightSolenoid, m_backRightSolenoid, m_backLeftSolenoid;
	TalonSRX m_leftArmMotor, m_rightArmMotor, m_cubeRotatorMotor;
	bool m_intakeIsClosed = false;
	double m_liftArmPosition;
	bool m_isArmGoingUp = false;
	bool m_isCubeTurningClockwise = false;

};

