#pragma once

#include "ctre/Phoenix.h"
#include "CORERobotLib.h"

using namespace CORE;

class IntakeSubsystem : public CORESubsystem {

public:
	IntakeSubsystem();
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
