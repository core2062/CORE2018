#pragma once

#include "ctre/Phoenix.h"
#include <WPILib.h>
#include "COREFramework/COREScheduler.h"
#include <CORERobotLib.h>
#include "COREHardware/COREJoystick.h"

using namespace CORE;

class IntakeSubsystem : public CORESubsystem {

public:
	IntakeSubsystem();
	void robotInit();
	void teleopInit();
	void teleop();
	bool isIntaking();
	void setIntakeSpeed(double);
	void openIntake();
	void closeIntake();
	TalonSRX m_leftIntakeMotor, m_rightIntakeMotor;
private:
	DoubleSolenoid m_leftIntakeSolenoid, m_rightIntakeSolenoid;
	double m_intakeMotorPercentage = 0.0;
};
