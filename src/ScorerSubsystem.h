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
	void rotateSetCube(double);
	void intakeCube();
	void outakeCube();
private:
	DoubleSolenoid m_frontLeftSolenoid, m_frontRightSolenoid, m_backRightSolenoid, m_backLeftSolenoid;
	TalonSRX m_leftArmMotor, m_rightArmMotor, m_cubeRotatorMotor;
	int m_rightYJoystick;
};
