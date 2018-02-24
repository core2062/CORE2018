#include "ScorerSubsystem.h"


// TODO fill these motors in with actual ports that we are going to be using
ScorerSubsystem::ScorerSubsystem() :
		m_frontLeftSolenoid(0, 1),
		m_frontRightSolenoid(0, 1),
		m_backRightSolenoid(0, 1),
		m_backLeftSolenoid(0, 1),
		m_leftArmMotor(2),
		m_rightArmMotor(3),
		m_cubeRotatorMotor(1) {

}

void ScorerSubsystem::robotInit() {
	operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
	operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER);
	operatorJoystick->registerAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y);
}

void ScorerSubsystem::teleopInit() {
}

void ScorerSubsystem::teleop() {
	double y = operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y);
	if (y >= 0.1 || y <= -0.1) {
		rotateSetCube(y);
	}
	if (operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
		intakeCube();
	}
	if (operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER)) {
		outakeCube();
	}
}

void ScorerSubsystem::rotateSetCube(double armMotorPercent) {
	m_leftArmMotor.Set(ControlMode::PercentOutput, armMotorPercent);
	m_rightArmMotor.Set(ControlMode::PercentOutput, armMotorPercent);
}

void ScorerSubsystem::intakeCube() {
	m_frontLeftSolenoid.Set(DoubleSolenoid::kForward);
	m_frontRightSolenoid.Set(DoubleSolenoid::kForward);
	m_backLeftSolenoid.Set(DoubleSolenoid::kForward);
	m_backRightSolenoid.Set(DoubleSolenoid::kForward);
}

void ScorerSubsystem::outakeCube() {
	m_frontLeftSolenoid.Set(DoubleSolenoid::kReverse);
	m_frontRightSolenoid.Set(DoubleSolenoid::kReverse);
	m_backLeftSolenoid.Set(DoubleSolenoid::kReverse);
	m_backRightSolenoid.Set(DoubleSolenoid::kReverse);
}
