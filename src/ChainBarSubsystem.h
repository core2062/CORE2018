#pragma once

#include <CORERobotLib.h>
#include <WPILib.h>
#include "ctre/Phoenix.h"
#include "COREUtilities/COREConstant.h"
#include "COREControl/COREPID.h"
#include "COREFramework/COREScheduler.h"

using namespace CORE;

class ChainBarSubsystem : public CORESubsystem, public CORETask {
public:
	ChainBarSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void postLoopTask() override;

	void SetChainBarSpeed(double speed);
    void SetChainBarRequestedAngle(double angle);
	void SetChainBarRequestedSpeed(double speed);
	double GetChainBarAngle(bool raw = false);

    void SetRotationSpeed(double speed);
    void SetRotationRequestedAngle(double angle);
	void SetRotationRequestedSpeed(double speed);
    double GetRotationAngle(bool raw = false);
    double GetRotationAngleRelativeToChainBar();

private:
    bool m_chainBarSet;
    bool m_rotationSet;
	TalonSRX m_chainBarMotor, m_rotationMotor;
	COREConstant<double> m_chainBarLowerTopLimit, m_chainBarUpperTopLimit, m_chainBarBottomLimit;
    COREConstant<double> m_liftChangePoint;
	COREConstant<double> m_chainBarAngleOffset, m_rotationAngleOffset;
    COREConstant<double> m_rotationTopLimit, m_rotationBottomLimit;
    COREConstant<double> m_chainBarUpP, m_chainBarUpI, m_chainBarUpD;
    COREConstant<double> m_chainBarDownP, m_chainBarDownI, m_chainBarDownD;
    COREConstant<double> m_rotationP, m_rotationI, m_rotationD;
    COREConstant<double> m_maxAngularAcceleration;
    COREPID m_chainBarPID, m_rotationPID;
	double m_requestedChainBarAngle, m_requestedChainBarSpeed;
    double m_requestedRotationAngle, m_requestedRotationSpeed;
};
