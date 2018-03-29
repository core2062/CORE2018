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

    void SetScaleHighHeight();
    void SetScaleMediumHeight();
    void SetScaleLowHeight();
    void SetSwitchHeight();
    void SetCubeClearanceHeight();
    void SetSafeHeight();

	int GetLiftPosition();
    double GetLiftInches();
	void resetEncoder();
	bool liftDown();

    bool IsAboveCubeClearanceHeight();
    bool IsAboveChangePoint();
    bool IsScaleLowHeight();
    bool IsScaleMediumHeight();
    bool IsScaleHighHeight();
    bool IsSwitchHeight();

private:
	TalonSRX m_leftMotor;
	TalonSRX m_rightMotor;
	COREConstant<double> m_bottomLimit;
	DigitalInput m_bottomLimitSwitch;
	COREConstant<double> m_switchHeight, m_scaleHighHeight, m_cubeClearanceHeight, m_cubeSafeHeight,
            m_scaleMediumHeight;
	COREConstant<int> m_topLimit;
	COREConstant<double> m_ticksPerInch;
    COREConstant<double> m_changePoint;
    COREConstant<int> m_cruiseVel, m_maxAcel;
	int m_requestedPosition;
    double m_requestedSpeed;
};
