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
	void SetForwardRotation();
	void SetBackwardsRotation();

    void SetRotationSpeed(double speed);
    void SetRotationRequestedAngle(double angle);
	void SetRotationRequestedSpeed(double speed);
    double GetRotationAngle(bool raw = false);
    double GetRotationAngleRelativeToChainBar();

    void SetIntakePosition();

    void SetRotationBackwardScore();
    void SetRotationForwardScore();

private:
	TalonSRX m_chainBarMotor, m_rotationMotor;
	COREConstant<double> m_chainBarLowerTopLimit, m_chainBarUpperTopLimit, m_chainBarBottomLimit;
    COREConstant<double> m_liftChangePoint;
	COREConstant<double> m_chainBarAngleOffset, m_rotationAngleOffset;
    COREConstant<double> m_rotationTopLimit, m_rotationBottomLimit;
    COREConstant<double> m_chainBarIntakePostionAngle, m_rotationIntakePostionAngle;
    COREConstant<double> m_forwardRotationScoringAngle, m_backwardsRotationScoringAngle;

    COREConstant<int> m_chainBarCruiseVel, m_chainBarMaxAcel;
	COREConstant<int> m_rotationCruiseVel, m_rotationMaxAcel;
	COREPID m_rotationPID;
	double m_requestedChainBarAngle, m_requestedChainBarSpeed;
    double m_requestedRotationAngle, m_requestedRotationSpeed;
};
