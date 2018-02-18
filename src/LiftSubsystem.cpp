#include <LiftSubsystem.h>
#include <CORERobotLib.h>
#include "COREUtilities/COREConstant.h"
#include "wpilib.h"

LiftSubsystem::LiftSubsystem(COREJoystick * operatorJoystick) :
		m_leftLiftMotor(0),
		m_rightLiftMotor(0),
		m_liftTopLimit("Lift Top Limit", 0),
		m_liftBottomLimit("Lift Bottom Limit", 0) {
	m_operatorJoystick = operatorJoystick;
	m_liftPosition = 0;
	m_leftYJoystickPosition = 0;
}

void LiftSubsystem::robotInit() {
	m_leftLiftMotor->Set(ControlMode::PercentOutput, 0);
	m_rightLiftMotor->Set(ControlMode::PercentOutput, 0);
	m_operatorJoystick->registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
}

void LiftSubsystem::teleopInit() {
}

void LiftSubsystem::teleop() {
	m_leftYJoystickPosition = m_operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	if (m_leftYJoystickPosition >= 0.1 || m_leftYJoystickPosition <= -0.1) {
		setLift(m_leftYJoystickPosition);
	}
}

void LiftSubsystem::isLifting() {
	SmartDashboard::PutNumber("Lift Position", m_liftPosition);
}

void LiftSubsystem::setLift(double liftMotorPercentage) {
	m_leftLiftMotor->Set(ControlMode::PercentOutput, liftMotorPercentage);
	m_rightLiftMotor->Set(ControlMode::PercentOutput, liftMotorPercentage);
}
