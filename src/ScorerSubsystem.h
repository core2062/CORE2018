#pragma once
#include "ctre/Phoenix.h"
#include "wpilib.h"
#include "COREHardware/COREJoystick.h"

class ScorerSubsystem {
public:
	ScorerSubsystem(COREJoystick * operatorJoystick);
	void robotInit();
	void teleopInit();
	void teleop();
	void rotateSetCube(double);
	void intakeCube();
	void outakeCube();
private:
	COREJoystick * m_operatorJoystick;
	DoubleSolenoid m_frontLeftSolenoid, m_frontRightSolenoid, m_backRightSolenoid, m_backLeftSolenoid;
	TalonSRX m_leftArmMotor, m_rightArmMotor, m_cubeRotatorMotor;
	int m_rightYJoystick;
};
