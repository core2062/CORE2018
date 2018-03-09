#include <LiftSubsystem.h>
#include "ctre/Phoenix.h"
#include "Robot.h"
#include "COREFramework/COREScheduler.h"

LiftSubsystem::LiftSubsystem() :
		m_leftLiftMotor(LEFT_LIFT_MOTOR_PORT),
		m_rightLiftMotor(RIGHT_LIFT_MOTOR_PORT),
		m_liftTopLimit("Lift Top Limit"),
		m_liftBottomLimitSwitch(LIFT_BOTTOM_LIMIT_SWITCH) {
	m_liftPosition = 0;
	m_leftLiftMotor.SetInverted(true);
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
}

void LiftSubsystem::teleop() {
	double y = -operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	if (y >= 0.01 && m_rightLiftMotor.GetSelectedSensorPosition(0) < m_liftTopLimit.Get()) {
		setLift(y*0.25);
	} else if (y <= -0.01 && !m_liftBottomLimitSwitch.Get()) {
		setLift(y*0.25);
	} else {
		setLift(0);
	}
    SmartDashboard::PutNumber("Lift Speed", y);

    SmartDashboard::PutNumber("Lift Encoder", m_rightLiftMotor.GetSelectedSensorPosition(0));
}

void LiftSubsystem::setLift(double liftMotorPercentage) {
	m_leftLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
	m_rightLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
}
