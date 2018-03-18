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
		m_gradualStopLimit("Gradual Stop Lift Limit"),
		m_maxAcceleration("Maximum Lift Acceleration"),
        m_leftLiftMotor(LEFT_LIFT_MOTOR_PORT),
        m_rightLiftMotor(RIGHT_LIFT_MOTOR_PORT),
        m_liftBottomLimitSwitch(LIFT_BOTTOM_LIMIT_SWITCH),
        m_liftPID(0.0, 0.0, 0.0) {
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
    SetRequestedPosition(GetLiftPosition());
}

void LiftSubsystem::teleop() {
    SmartDashboard::PutNumber("Lift Encoder", m_rightLiftMotor.GetSelectedSensorPosition(0));
    SmartDashboard::PutNumber("Current Lift Position", GetLiftPosition());
    SmartDashboard::PutNumber("Requested Lift Position", m_requestedPosition);
    double liftSpeed = -operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
    double liftPosition = GetLiftPosition();
    SmartDashboard::PutNumber("Lift Speed", liftSpeed);
    if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::X_BUTTON)) {
 	   SetRequestedPosition(200000);
    }
    if (abs(liftSpeed) > 0.01) {
    	if (liftSpeed < 0) {
    		liftSpeed = liftSpeed * 0.25;
    	} else {
    		liftSpeed *= 0.5;
    	}
            SetRequestedPosition(GetLiftPosition());
    } else {
        if (m_requestedPosition > liftPosition) {
            m_liftPID.setProportionalConstant(m_liftUpP.Get());
            m_liftPID.setIntegralConstant(m_liftUpI.Get());
            m_liftPID.setDerivativeConstant(m_liftUpD.Get());
            liftSpeed = m_liftPID.calculate(m_requestedPosition - liftPosition);
        } else {
            m_liftPID.setProportionalConstant(m_liftDownP.Get());
            m_liftPID.setIntegralConstant(m_liftDownI.Get());
            m_liftPID.setDerivativeConstant(m_liftDownD.Get());
            liftSpeed = m_liftPID.calculate(m_requestedPosition - liftPosition);
        }
    }

    if (liftSpeed > 0 && liftPosition > m_liftTopLimit.Get()) {
		liftSpeed = 0;
	} else if (liftSpeed < 0 && m_liftBottomLimitSwitch.Get()) {
		liftSpeed = 0;
		resetEncoder();
		SetRequestedPosition(0);
	}

	double maxAllowedSpeed = sqrt(2 * (m_requestedPosition - liftPosition) *
			 m_maxAcceleration.Get());
	if (fabs(liftSpeed) > maxAllowedSpeed) {
		liftSpeed = maxAllowedSpeed * (liftSpeed / fabs(liftSpeed));
	}

    m_currentLiftSpeed = liftSpeed;
    setLift(liftSpeed);
    SmartDashboard::PutNumber("Lift Position", liftPosition);
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

double LiftSubsystem::GetLiftPosition() {
    return m_rightLiftMotor.GetSelectedSensorPosition(0);
}
