#include <IntakeSubsystem.h>
#include <CORERobotLib.h>
#include <ctre/Phoenix.h>
// TODO fill this in with actual motor ports and solenoid stuff
IntakeSubsystem::IntakeSubsystem(COREJoystick * operatorJoystick) :
		m_leftIntakeMotor(0),
		m_rightIntakeMotor(0),
		m_leftIntakeSolenoid(0, 1, 2),
		m_rightIntakeSolenoid(0, 1, 2) {
	m_intakeMotorPercentage = 0;
	m_operatorJoystick = operatorJoystick;
}

void IntakeSubsystem::robotInit() {
	m_leftIntakeMotor.Set(ControlMode::PercentOutput, 0);
	m_operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON);
}
void IntakeSubsystem::teleopInit() {

}
void IntakeSubsystem::teleop() {
	if (m_operatorJoystick->getRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
		openIntake();
	}
	if (m_operatorJoystick->getRisingEdge(CORE::COREJoystick::JoystickButton::B_BUTTON)) {
		closeIntake();
	}
	if (m_operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)) {
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
