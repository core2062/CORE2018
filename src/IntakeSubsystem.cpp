#include "IntakeSubsystem.h"

#include "Robot.h"

// TODO fill this in with actual motor ports and solenoid stuff
IntakeSubsystem::IntakeSubsystem() :
		m_leftIntakeMotor(0),
		m_rightIntakeMotor(0),
		m_operatorJoystick(0),
		m_leftIntakeSolenoid(LEFT_INTAKE_IN_SOLENOID_PORT, LEFT_INTAKE_OUT_SOLENOID_PORT),
		m_rightIntakeSolenoid(RIGHT_INTAKE_IN_SOLENOID_PORT, RIGHT_INTAKE_OUT_SOLENOID_PORT, 2) {
	m_intakeMotorPercentage = 0;

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
		setIntake(0.2);
	} else {
		setIntake(0);
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

void IntakeSubsystem::setIntake(double intakeMotorPercent) {
	m_leftIntakeMotor.Set(ControlMode::PercentOutput, m_intakeMotorPercentage);
	m_rightIntakeMotor.Set(ControlMode::PercentOutput, m_intakeMotorPercentage);
}
