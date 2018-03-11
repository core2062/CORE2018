#include "IntakeSubsystem.h"
#include "ctre/Phoenix.h"
#include "Robot.h"
#include "COREFramework/COREScheduler.h"
#include <WPILib.h>

// TODO fill this in with actual motor ports and solenoid stuff
IntakeSubsystem::IntakeSubsystem() :
		m_leftIntakeMotor(LEFT_INTAKE_MOTOR_PORT),
		m_rightIntakeMotor(RIGHT_INTAKE_MOTOR_PORT),
		m_intakeSolenoid(INTAKE_IN_SOLENOID_PORT, INTAKE_OUT_SOLENOID_PORT){
	m_rightIntakeMotor.SetInverted(true);
}

void IntakeSubsystem::robotInit() {
	m_leftIntakeMotor.Set(ControlMode::PercentOutput, 0);
	operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON);
}

void IntakeSubsystem::teleopInit() {

}

void IntakeSubsystem::teleop() {
	if (operatorJoystick->getRisingEdge(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER)) {
		openIntake();
		setIntakeSpeed(-0.2);
	} else if (operatorJoystick->getRisingEdge(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)) {
		closeIntake();
		setIntakeSpeed(-0.2);
	} else if (operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
		closeIntake();
		setIntakeSpeed(0.2);
	} else {
		setIntakeSpeed(0);
	}
}

void IntakeSubsystem::openIntake() {
	m_intakeSolenoid.Set(DoubleSolenoid::kReverse);
}

void IntakeSubsystem::closeIntake() {
	m_intakeSolenoid.Set(DoubleSolenoid::kForward);
}

void IntakeSubsystem::setIntakeSpeed(double intakeMotorPercent) {
	m_leftIntakeMotor.Set(ControlMode::PercentOutput, m_intakeMotorPercentage);
	m_rightIntakeMotor.Set(ControlMode::PercentOutput, m_intakeMotorPercentage);
}
