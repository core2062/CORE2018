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

class LiftSubsystem : public CORESubsystem, public CORETask {
public:
	LiftSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void setLift(double speed);
	void SetRequestedPosition(double position);
    void postLoopTask() override;
    void SetRequestedSpeed(double speed);
    void SetScaleHighHeight();
    void SetScaleMediumHeight();
    void SetScaleLowHeight();
    void SetSwitchHeight();
    void SetCubeClearanceHeight();
    void SetCubeSafeHeight();
    void SetCubeAboveSafeHeight();
	double GetLiftPosition();
    double GetLiftInches();
	void resetEncoder();
	bool liftDown();

private:
	TalonSRX m_leftMotor;
	TalonSRX m_rightMotor;
	COREConstant<double> m_topLimit;
	COREConstant<double> m_upP, m_upI, m_upD;
	COREConstant<double> m_downP, m_downI, m_downD;
	COREConstant<double> m_bottomLimit;
	DigitalInput m_bottomLimitSwitch;
	COREPID m_PID;
	double m_requestedPosition, m_requestedSpeed;
	COREConstant<double> m_switchHeight, m_scaleHighHeight, m_scaleLowHeight,
		m_cubeClearanceHeight, m_cubeSafeHeight, m_scaleMediumHeight;
	COREConstant<double> m_ticksPerInch;
};
