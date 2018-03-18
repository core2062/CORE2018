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
	void SetRequestedPosition(double position);
	double GetLiftPosition();
	void resetEncoder();

private:
	TalonSRX m_leftLiftMotor;
	TalonSRX m_rightLiftMotor;
	COREConstant<double> m_liftTopLimit;
	COREConstant<double> m_liftUpP, m_liftUpI, m_liftUpD;
	COREConstant<double> m_liftDownP, m_liftDownI, m_liftDownD;
	COREConstant<double> m_liftBottomLimit;
	COREConstant<double> m_gradualStopLimit;
	COREConstant<double> m_maxAcceleration;
	DigitalInput m_liftBottomLimitSwitch;
	COREPID m_liftPID;
	double m_requestedPosition;
	double m_currentLiftSpeed;
};
