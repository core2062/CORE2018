#include <LiftSubsystem.h>
#include "ctre/Phoenix.h"
#include "Robot.h"
#include "COREFramework/COREScheduler.h"

LiftSubsystem::LiftSubsystem() :
		m_leftLiftMotor(LEFT_LIFT_MOTOR_PORT),
		m_rightLiftMotor(RIGHT_LIFT_MOTOR_PORT),
		m_liftTopLimit("Lift Top Limit", 0),
		m_liftBottomLimit("Lift Bottom Limit", 0) {
	m_liftPosition = 0;
	m_leftLiftMotor.SetInverted(true);
}

void LiftSubsystem::robotInit() {
	m_leftLiftMotor.Set(ControlMode::PercentOutput, 0);
	m_rightLiftMotor.Set(ControlMode::PercentOutput, 0);
    operatorJoystick->registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
}

void LiftSubsystem::teleopInit() {
}

void LiftSubsystem::teleop() {
	SmartDashboard::PutNumber("Right Lift Motor Position", m_rightLiftMotor.GetSensorCollection().GetQuadraturePosition());
	double y = operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	if (abs(y) >= 0.1) {
		setLift(y);
	}
}

void LiftSubsystem::setLift(double liftMotorPercentage) {
	m_leftLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
	m_rightLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
}
