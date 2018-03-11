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
        m_liftBottomLimit("LiftBottom Limit"),
        m_leftLiftMotor(LEFT_LIFT_MOTOR_PORT),
        m_rightLiftMotor(RIGHT_LIFT_MOTOR_PORT),
        m_liftBottomLimitSwitch(LIFT_BOTTOM_LIMIT_SWITCH),
        m_liftPID(0.0, 0.0, 0.0) {
    m_liftPosition = 0;
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
}

void LiftSubsystem::teleopInit() {
    m_liftPID.setProportionalConstant(m_liftUpP.Get());
    m_liftPID.setIntegralConstant(m_liftUpI.Get());
    m_liftPID.setDerivativeConstant(m_liftUpD.Get());
}

void LiftSubsystem::teleop() {
    SmartDashboard::PutNumber("Lift Encoder", m_rightLiftMotor.GetSelectedSensorPosition(0));
/*in progress code*/
    double liftSpeed = -operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
    SmartDashboard::PutNumber("Lift Speed", liftSpeed);
    double liftHeight = m_rightLiftMotor.GetSelectedSensorPosition(0);
    if (abs(liftSpeed) > 0.01) {
        if (liftSpeed > 0 && liftHeight > m_liftTopLimit.Get()) {
            liftSpeed = 0;
        } else if (liftSpeed < 0 && m_liftBottomLimitSwitch.Get()) {
            liftSpeed = 0;
        }
    } /*else {
        if (liftSpeed > liftHeight) {
            m_liftPID.setProportionalConstant(m_liftUpP.Get());
            m_liftPID.setIntegralConstant(m_liftUpI.Get());
            m_liftPID.setDerivativeConstant(m_liftUpD.Get());
            liftSpeed = m_liftPID.calculate(m_liftPosition - liftHeight);
        } else {
            m_liftPID.setProportionalConstant(m_liftUpP.Get());
            m_liftPID.setIntegralConstant(m_liftUpI.Get());
            m_liftPID.setDerivativeConstant(m_liftUpD.Get());
            liftSpeed = m_liftPID.calculate(m_liftPosition - liftHeight);
        }
    }*/
    setLift(liftSpeed);
    SmartDashboard::PutNumber("Lift Height", liftHeight);
}

void LiftSubsystem::setLift(double liftMotorPercentage) {
    m_leftLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
    m_rightLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
}
