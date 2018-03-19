#include <LiftSubsystem.h>
#include "ctre/Phoenix.h"
#include "Robot.h"
#include "COREFramework/COREScheduler.h"
#include "COREControl/COREPID.h"
#include <WPILib.h>

LiftSubsystem::LiftSubsystem() :
        m_liftTopLimit("Lift Top Limit"),
        m_liftUpP("Lift Up P"),
        m_liftUpI("Lift Up I"),
        m_liftUpD("Lift Up D"),
		m_liftDownP("Lift Down P"),
		m_liftDownI("Lift Down I"),
		m_liftDownD("Lift Down D"),
        m_liftBottomLimit("LiftBottom Limit"),
        m_leftLiftMotor(LEFT_LIFT_MOTOR_PORT),
        m_rightLiftMotor(RIGHT_LIFT_MOTOR_PORT),
        m_liftBottomLimitSwitch(LIFT_BOTTOM_LIMIT_SWITCH),
        m_liftPID(0.0, 0.0, 0.0),
        m_liftTicksPerInch("Lift Ticks Per Inch") {
    m_rightLiftMotor.SetInverted(true);

}

void LiftSubsystem::robotInit() {
    m_leftLiftMotor.Set(ControlMode::PercentOutput, 0);
    m_rightLiftMotor.Set(ControlMode::PercentOutput, 0);
    m_leftLiftMotor.SetNeutralMode(NeutralMode::Brake);
    m_rightLiftMotor.SetNeutralMode(NeutralMode::Brake);
    m_rightLiftMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_rightLiftMotor.SetSelectedSensorPosition(0, 0, 0);
    m_rightLiftMotor.SetSensorPhase(true);
    operatorJoystick->registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
    operatorJoystick->registerButton(CORE::COREJoystick::X_BUTTON);
}

void LiftSubsystem::teleopInit() {
    m_liftPID.setProportionalConstant(m_liftUpP.Get());
    m_liftPID.setIntegralConstant(m_liftUpI.Get());
    m_liftPID.setDerivativeConstant(m_liftUpD.Get());
    SetRequestedPosition(GetLiftInches());
}

void LiftSubsystem::teleop() {
    SetRequestedSpeed(-operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y));
}

void LiftSubsystem::resetEncoder() {
	m_rightLiftMotor.SetSelectedSensorPosition(0, 0, 0);
}

void LiftSubsystem::setLift(double liftMotorPercentage) {
    m_leftLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
    m_rightLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
}

void LiftSubsystem::SetRequestedPosition(double position) {
    m_requestedPosition = position;
}

void LiftSubsystem::SetRequestedSpeed(double speed) {
    m_requestedSpeed = speed;
}

double LiftSubsystem::GetLiftPosition() {
    return m_rightLiftMotor.GetSelectedSensorPosition(0);
}

double LiftSubsystem::GetLiftInches() {
    return GetLiftPosition() / m_liftTicksPerInch.Get();
}

void LiftSubsystem::postLoopTask() {
    SmartDashboard::PutNumber("Lift Encoder", m_rightLiftMotor.GetSelectedSensorPosition(0));
    SmartDashboard::PutNumber("Current Lift Ticks", GetLiftPosition());
    SmartDashboard::PutNumber("Current Lift Inches", GetLiftInches());
    SmartDashboard::PutNumber("Requested Lift Position", m_requestedPosition);

    double liftPosition = GetLiftInches();
    SmartDashboard::PutNumber("Lift Speed", m_requestedSpeed);
    if (abs(m_requestedSpeed) > 0.01) {
        if (m_requestedSpeed < 0) {
            m_requestedSpeed *= 0.1;
        } else {
            m_requestedSpeed *= 0.5;
        }
        SetRequestedPosition(GetLiftInches());
    } else {
        if (m_requestedPosition > liftPosition) {
            m_liftPID.setProportionalConstant(m_liftUpP.Get());
            m_liftPID.setIntegralConstant(m_liftUpI.Get());
            m_liftPID.setDerivativeConstant(m_liftUpD.Get());
            m_requestedSpeed = m_liftPID.calculate(m_requestedPosition * m_liftTicksPerInch.Get() - GetLiftPosition());
        } else {
            m_liftPID.setProportionalConstant(m_liftDownP.Get());
            m_liftPID.setIntegralConstant(m_liftDownI.Get());
            m_liftPID.setDerivativeConstant(m_liftDownD.Get());
            m_requestedSpeed = m_liftPID.calculate(m_requestedPosition * m_liftTicksPerInch.Get() - GetLiftPosition());
        }
    }
    if (m_requestedSpeed > 0 && liftPosition > m_liftTopLimit.Get()) {
        m_requestedSpeed = 0;
    } else if (m_liftBottomLimitSwitch.Get()) {
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
