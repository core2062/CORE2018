#include <LiftSubsystem.h>

#include "Robot.h"

LiftSubsystem::LiftSubsystem() :
		m_leftLiftMotor(RIGHT_LIFT_MOTOR_PORT),
		m_rightLiftMotor(LEFT_LIFT_MOTOR_PORT),
		m_liftTopLimit("Lift Top Limit", 0),
		m_liftBottomLimit("Lift Bottom Limit", 0) {
	m_liftPosition = 0;
	m_rightLiftMotor.SetInverted(true);
}

void LiftSubsystem::robotInit() {
	m_leftLiftMotor.Set(ControlMode::PercentOutput, 0);
	m_rightLiftMotor.Set(ControlMode::PercentOutput, 0);
    operatorJoystick->registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
}

void LiftSubsystem::teleopInit() {
}

void LiftSubsystem::teleop() {
	double y = operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	if (abs(y) >= 0.1) {
		setLift(y);
	}
}

void LiftSubsystem::setLift(double liftMotorPercentage) {
	m_leftLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
	m_rightLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
}
