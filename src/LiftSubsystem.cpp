#include <LiftSubsystem.h>
#include "ctre/Phoenix.h"
#include "Robot.h"
#include "COREFramework/COREScheduler.h"
#include "COREControl/COREPID.h"
#include <WPILib.h>

LiftSubsystem::LiftSubsystem() :
        m_topLimit("Lift Top Limit"),
        m_upP("Lift Up P"),
        m_upI("Lift Up I"),
        m_upD("Lift Up D"),
		m_downP("Lift Down P"),
		m_downI("Lift Down I"),
		m_downD("Lift Down D"),
        m_bottomLimit("Lift Bottom Limit"),
        m_leftMotor(LEFT_LIFT_MOTOR_PORT),
        m_rightMotor(RIGHT_LIFT_MOTOR_PORT),
        m_bottomLimitSwitch(LIFT_BOTTOM_LIMIT_SWITCH_PORT),
        m_PID(0.0, 0.0, 0.0),
        m_ticksPerInch("Lift Ticks Per Inch"),
		m_scaleMediumHeight("Lift Medium Height"),
		m_scaleLowHeight("Scale Low Height"),
		m_scaleHighHeight("Scale High Height"),
		m_switchHeight("Switch Height"),
		m_cubeSafeHeight("Cube Safe Height"),
		m_cubeClearanceHeight("Cube Clearance Height") {
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
    operatorJoystick->registerButton(CORE::COREJoystick::X_BUTTON);
}

void LiftSubsystem::teleopInit() {
    m_PID.setProportionalConstant(m_upP.Get());
    m_PID.setIntegralConstant(m_upI.Get());
    m_PID.setDerivativeConstant(m_upD.Get());
    SetRequestedPosition(GetLiftInches());
}

void LiftSubsystem::teleop() {
    SetRequestedSpeed(-operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y));
}

void LiftSubsystem::resetEncoder() {
	m_rightMotor.SetSelectedSensorPosition(0, 0, 0);
}

void LiftSubsystem::setLift(double liftMotorPercentage) {
    m_rightMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
}

void LiftSubsystem::SetRequestedPosition(double position) {
    m_requestedPosition = position;
}

void LiftSubsystem::SetRequestedSpeed(double speed) {
    m_requestedSpeed = speed;
}

double LiftSubsystem::GetLiftPosition() {
    return m_rightMotor.GetSelectedSensorPosition(0);
}

double LiftSubsystem::GetLiftInches() {
    return GetLiftPosition() / m_ticksPerInch.Get();
}

void LiftSubsystem::postLoopTask() {
    SmartDashboard::PutNumber("Lift Encoder", m_rightMotor.GetSelectedSensorPosition(0));
    SmartDashboard::PutNumber("Current Lift Ticks", GetLiftPosition());
    SmartDashboard::PutNumber("Current Lift Inches", GetLiftInches());
    SmartDashboard::PutNumber("Requested Lift Position", m_requestedPosition);

    double liftPosition = GetLiftInches();
    SmartDashboard::PutNumber("Lift Speed", m_requestedSpeed);
    if (abs(m_requestedSpeed) > 0.01) {
        if (m_requestedSpeed < 0) {
            m_requestedSpeed *= 0.2;
        } else {
            m_requestedSpeed *= 0.5;
        }
        SetRequestedPosition(GetLiftInches());
    } else {
        if (m_requestedPosition > liftPosition) {
            m_PID.setProportionalConstant(m_upP.Get());
            m_PID.setIntegralConstant(m_upI.Get());
            m_PID.setDerivativeConstant(m_upD.Get());
            m_requestedSpeed = m_PID.calculate(m_requestedPosition * m_ticksPerInch.Get() - GetLiftPosition());
        } else {
            m_PID.setProportionalConstant(m_downP.Get());
            m_PID.setIntegralConstant(m_downI.Get());
            m_PID.setDerivativeConstant(m_downD.Get());
            m_requestedSpeed = m_PID.calculate(m_requestedPosition * m_ticksPerInch.Get() - GetLiftPosition());
        }
    }
    if (m_requestedSpeed > 0 && liftPosition > m_topLimit.Get()) {
        m_requestedSpeed = 0;
    } else if (m_bottomLimitSwitch.Get()) {
        if(m_requestedSpeed <= 0) {
            m_requestedSpeed = 0;
            SetRequestedPosition(0);
        }
        resetEncoder();
    }

    setLift(m_requestedSpeed);
    m_requestedSpeed = 0;
    SmartDashboard::PutNumber("Lift Position", liftPosition);
}

bool LiftSubsystem::liftDown() {
    return m_bottomLimitSwitch.Get();
}

void LiftSubsystem::SetScaleHighHeight() {
	SetRequestedPosition(m_scaleHighHeight.Get());
}

void LiftSubsystem::SetScaleLowHeight() {
	SetRequestedPosition(m_scaleLowHeight.Get());
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

void LiftSubsystem::SetCubeSafeHeight() {
	SetRequestedPosition(m_cubeSafeHeight.Get());
}

void LiftSubsystem::SetCubeAboveSafeHeight() {
	SetRequestedPosition(m_cubeSafeHeight.Get() + 5.0);
}
