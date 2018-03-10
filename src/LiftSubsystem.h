#pragma once

#include "ctre/Phoenix.h"
#include "WPILib.h"
#include <CORERobotLib.h>
#include "COREHardware/COREJoystick.h"
#include "COREUtilities/COREConstant.h"
#include "COREFramework/COREScheduler.h"
#include "COREControl/COREPID.h"


using namespace CORE;
using namespace frc;

class LiftSubsystem : public CORESubsystem {
public:
	LiftSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void setLift(double speed);
	void setLiftSwitch(double setPoint);
	void setLiftScale(double setPoint);
	double m_liftPosition;

private:
	TalonSRX m_leftLiftMotor;
	TalonSRX m_rightLiftMotor;
	COREJoystick * m_operatorJoystick;
	COREConstant<double> m_liftTopLimit;
	COREConstant<double> m_liftUpP, m_liftUpI, m_liftUpD;
	COREConstant<double> m_liftBottomLimit;
	DigitalInput m_liftBottomLimitSwitch;
	COREPID m_liftPID;
};
