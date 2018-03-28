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
	void SetRequestedPosition(double positionInInches);
    void postLoopTask() override;
    void SetRequestedSpeed(double speed);
	int GetLiftPosition();
    double GetLiftInches();
	void resetEncoder();
	bool liftDown();

    void SetScaleLowHeight();
    void SetScaleMediumHeight();
    void SetSwitchHeight();
    void SetCubeClearanceHeight();
    void SetSafeHeight();
    void SetScaleHighHeight();

    bool IsLiftAboveCubeClearanceHeight();

private:
	TalonSRX m_leftMotor;
	TalonSRX m_rightMotor;
	COREConstant<int> m_topLimit;
	COREConstant<double> m_ticksPerInch;
    COREConstant<int> m_cruiseVel, m_maxAcel;
	DigitalInput m_bottomLimitSwitch;
	int m_requestedPosition;
    double m_requestedSpeed;
    COREConstant<double> m_switchHeight, m_scaleHighHeight, m_scaleLowHeight,
            m_cubeClearanceHeight, m_safeHeight, m_scaleMediumHeight;
};
