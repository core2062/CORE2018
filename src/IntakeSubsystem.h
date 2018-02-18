#pragma once

#include "ctre/Phoenix.h"
#include "CORERobotLib.h"
#include "Robot.h"

class IntakeSubsystem {

public:
	IntakeSubsystem(COREJoystick * operatorJoystick);
	void robotInit();
	void teleopInit();
	void teleop();
	bool isIntaking();
	void setIntake(double);
	void openIntake();
	void closeIntake();
	TalonSRX m_leftIntakeMotor, m_rightIntakeMotor;
private:
	COREJoystick * m_operatorJoystick;
	DoubleSolenoid m_leftIntakeSolenoid, m_rightIntakeSolenoid;
	double m_intakeMotorPercentage;
};
