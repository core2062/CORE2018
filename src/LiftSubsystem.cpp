#include <LiftSubsystem.h>
#include "ctre/Phoenix.h"
#include "Robot.h"
#include "COREFramework/COREScheduler.h"
#include "COREControl/COREPID.h"
#include <WPILib.h>

LiftSubsystem::LiftSubsystem() :
        m_topLimit("Lift Top Limit"),
        m_ticksPerInch("Lift Ticks Per Inch"),
        m_leftMotor(LEFT_LIFT_MOTOR_PORT),
        m_rightMotor(RIGHT_LIFT_MOTOR_PORT),
        m_bottomLimitSwitch(LIFT_BOTTOM_LIMIT_SWITCH_PORT),
        m_cruiseVel("Lift Cruise Velocity"),
        m_maxAcel("Lift Max Acceleration"),
		m_bottomLimit("Lift Bottom Limit"),
        m_scaleMediumHeight("Lift Scale Medium Height"),
        m_scaleHighHeight("Lift Scale High Height"),
        m_switchHeight("Lift Switch Height"),
        m_cubeClearanceHeight("Lift Cube Clearance Height"),
        m_changePoint("Lift Change Point"),
        m_cubeSafeHeight("Lift Safe Height") {
    m_rightMotor.SetInverted(true);

}

void LiftSubsystem::robotInit() {
    m_leftMotor.Set(ControlMode::PercentOutput, 0);
    m_rightMotor.Set(ControlMode::PercentOutput, 0);

    m_leftMotor.SetNeutralMode(NeutralMode::Brake);
    m_rightMotor.SetNeutralMode(NeutralMode::Brake);

    m_leftMotor.Follow(m_rightMotor);

    m_rightMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_rightMotor.SetSelectedSensorPosition(0, 0, 0);

    m_rightMotor.SetSensorPhase(true);

    operatorJoystick->registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
    operatorJoystick->registerButton(CORE::COREJoystick::START_BUTTON);
}

void LiftSubsystem::teleopInit() {
//    m_PID.setProportionalConstant(m_upP.Get());
//    m_PID.setIntegralConstant(m_upI.Get());
//    m_PID.setDerivativeConstant(m_upD.Get());
    //SetRequestedPosition(GetLiftInches());
    SetRequestedPosition(GetLiftInches());
    m_rightMotor.ConfigMotionCruiseVelocity(m_cruiseVel.Get(), 0);
    m_rightMotor.ConfigMotionAcceleration(m_maxAcel.Get(), 0);
}

void LiftSubsystem::teleop() {

}

void LiftSubsystem::resetEncoder() {
	m_rightMotor.SetSelectedSensorPosition(0, 0, 0);
}

/*
 * Set requested position in inches of the lift
 * Limited so that lift can not go below or above limits
 */
void LiftSubsystem::SetRequestedPosition(double positionInInches) {
    auto position = (int)(positionInInches * m_ticksPerInch.Get());
    position = max(position, 0);
    position = min(position, (int)(m_topLimit.Get() * m_ticksPerInch.Get()));
    m_requestedPosition = position;
}

void LiftSubsystem::SetRequestedSpeed(double speed) {
    m_requestedSpeed = speed;
}

int LiftSubsystem::GetLiftPosition() {
    return m_rightMotor.GetSelectedSensorPosition(0);
}

double LiftSubsystem::GetLiftInches() {
    return GetLiftPosition() / m_ticksPerInch.Get();
}

void LiftSubsystem::postLoopTask() {
    SmartDashboard::PutNumber("Lift Position", m_rightMotor.GetSelectedSensorPosition(0));
    SmartDashboard::PutNumber("Lift Velocity", m_rightMotor.GetSelectedSensorVelocity(0));
    SmartDashboard::PutNumber("Requested Lift Position", m_requestedPosition);

    double liftPosition = GetLiftInches();

    SetRequestedSpeed(-operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y));

    SmartDashboard::PutNumber("Lift Speed", m_requestedSpeed);
    if (m_requestedSpeed < -0.01 || m_requestedSpeed > 0.1) {
        if (m_requestedSpeed < 0) {
            m_requestedSpeed *= 0.1;
        } else {
            m_requestedSpeed *= 0.5;
        }
        SetRequestedPosition(liftPosition);
        CORE2018::GetInstance()->superStructure.setWantedState(WantedState::MANUAL);
    }

    double liftRequestedPosition = m_requestedPosition;

    if (m_requestedSpeed > 0 && liftPosition > m_topLimit.Get()) {
        m_requestedSpeed = 0;
        SetRequestedPosition(m_topLimit.Get());
    } else if (liftDown()) {
        if(m_requestedSpeed < 0) {
            m_requestedSpeed = 0;
            SetRequestedPosition(0);
        }
        resetEncoder();
    }

    if ((m_requestedPosition / m_ticksPerInch.Get()) < m_changePoint.Get() && GetLiftInches() >  m_changePoint.Get()) {
        if (CORE2018::GetInstance()->chainBarSubsystem.IsChainBarAboveLowerTopLimit()) {
            if (GetLiftInches() < m_changePoint.Get()) {
                m_requestedSpeed = 0;
            }
            liftRequestedPosition = m_changePoint.Get() * m_ticksPerInch.Get();
            CORE2018::GetInstance()->chainBarSubsystem.SetChainBarRequestedAngle(-10);
            CORELog::logInfo("Lift waiting for chain bar");
        }
        CORELog::logInfo("Lift less than change point");
    }

    if (m_requestedSpeed < -0.01 || m_requestedSpeed > 0.1) {
        m_rightMotor.Set(ControlMode::PercentOutput, m_requestedSpeed);
    } else {
        m_rightMotor.Set(ControlMode::MotionMagic, liftRequestedPosition);
    }


    m_requestedSpeed = 0;
    SmartDashboard::PutNumber("Lift Inches", liftPosition);
}

bool LiftSubsystem::liftDown() {
    return m_bottomLimitSwitch.Get();
}

void LiftSubsystem::SetScaleHighHeight() {
    SetRequestedPosition(m_scaleHighHeight.Get());
}

void LiftSubsystem::SetScaleMediumHeight() {
    SetRequestedPosition(m_scaleMediumHeight.Get());
}

void LiftSubsystem::SetSwitchHeight() {
    SetRequestedPosition(m_switchHeight.Get());
}

void LiftSubsystem::SetCubeClearanceHeight() {
    SetRequestedPosition(m_cubeClearanceHeight.Get());
}

void LiftSubsystem::SetSafeHeight() {
    SetRequestedPosition(m_cubeSafeHeight.Get());
}

bool LiftSubsystem::IsAboveCubeClearanceHeight() {
    return GetLiftInches() > m_cubeClearanceHeight.Get() - 1;
}

bool LiftSubsystem::IsAboveChangePoint() {
    return GetLiftInches() > m_changePoint.Get();
}

bool LiftSubsystem::IsScaleMediumHeight() {
    return abs(GetLiftInches() - m_scaleMediumHeight.Get()) < 2;
}

bool LiftSubsystem::IsScaleHighHeight() {
    return abs(GetLiftInches() - m_scaleHighHeight.Get()) < 2;
}

bool LiftSubsystem::IsSwitchHeight() {
    return abs(GetLiftInches() - m_switchHeight.Get()) < 2;
}
