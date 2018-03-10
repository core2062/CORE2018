#include "IntakeSubsystem.h"
#include "ctre/Phoenix.h"
#include "Robot.h"
#include "COREFramework/COREScheduler.h"
#include <WPILib.h>

// TODO fill this in with actual motor ports and solenoid stuff
IntakeSubsystem::IntakeSubsystem() :
		m_leftIntakeMotor(LEFT_INTAKE_MOTOR_PORT),
		m_rightIntakeMotor(RIGHT_INTAKE_MOTOR_PORT),
		m_leftIntakeSolenoid(LEFT_INTAKE_IN_SOLENOID_PORT, LEFT_INTAKE_OUT_SOLENOID_PORT),
		m_rightIntakeSolenoid(RIGHT_INTAKE_IN_SOLENOID_PORT, RIGHT_INTAKE_OUT_SOLENOID_PORT) {

}

void IntakeSubsystem::robotInit() {
	m_leftIntakeMotor.Set(ControlMode::PercentOutput, 0);
	operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON);
}

void IntakeSubsystem::teleopInit() {

}

void IntakeSubsystem::teleop() {
	if (operatorJoystick->getRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
		openIntake();
	}
	if (operatorJoystick->getRisingEdge(CORE::COREJoystick::JoystickButton::B_BUTTON)) {
		closeIntake();
	}
	if (operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)) {
		setIntakeSpeed(0.2);
	} else {
		setIntakeSpeed(0);
	}
}

void IntakeSubsystem::openIntake() {
	m_leftIntakeSolenoid.Set(DoubleSolenoid::kReverse);
	m_rightIntakeSolenoid.Set(DoubleSolenoid::kReverse);
}

void IntakeSubsystem::closeIntake() {
	m_leftIntakeSolenoid.Set(DoubleSolenoid::kForward);
	m_rightIntakeSolenoid.Set(DoubleSolenoid::kForward);
}

void IntakeSubsystem::setIntakeSpeed(double intakeMotorPercent) {
	m_leftIntakeMotor.Set(ControlMode::PercentOutput, m_intakeMotorPercentage);
	m_rightIntakeMotor.Set(ControlMode::PercentOutput, m_intakeMotorPercentage);
}
