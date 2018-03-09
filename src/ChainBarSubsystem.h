#pragma once

#include <CORERobotlib.h>
#include <WPILib.h>
#include "COREUtilities/COREConstant.h"
#include "COREHardware/COREJoystick.h"
#include "ctre/Phoenix.h"

using namespace CORE;

class ChainBarSubsystem : public CORESubsystem {
public:
	ChainBarSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void setChainBar(double speed);
	void setRotation(double speed);
private:
	TalonSRX m_chainBarMotor, m_rotationMotor;
	COREConstant<double> m_chainBarLowerTopLimit;
	COREConstant<double> m_chainBarUpperTopLimit;
	COREConstant<double> m_chainBarBottomLimit;
	COREConstant<double> m_liftChangePoint;
	double m_chainBarPosition;
	double m_liftPosition;
};
