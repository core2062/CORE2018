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
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void wideRangeIntake();
	void smallRangeIntake();
	void outtakeCube();
	void setIntakeSpeed(double);
	void openIntake();
	void closeIntake();
	TalonSRX m_leftIntakeMotor, m_rightIntakeMotor;
private:
	DoubleSolenoid m_intakeSolenoid;
	double m_intakeMotorPercentage = 0.0;
};
