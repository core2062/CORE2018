#pragma once

#include "ctre/Phoenix.h"
#include "WPILib.h"
#include <CORERobotLib.h>
#include "COREHardware/COREJoystick.h"
#include "COREUtilities/COREConstant.h"

using namespace CORE;
using namespace frc;

class LiftSubsystem : public CORESubsystem {
public:
	LiftSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void setLift(double speed);
	double m_liftPosition;

private:
	TalonSRX m_leftLiftMotor;
	TalonSRX m_rightLiftMotor;
	COREJoystick * m_operatorJoystick;
	COREConstant<double> m_liftTopLimit;
	DigitalInput m_liftBottomLimitSwitch;
};
