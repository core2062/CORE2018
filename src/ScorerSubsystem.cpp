#include <ScorerSubsystem.h>

#include "Robot.cpp"

ScorerSubsystem::ScorerSubsystem() :
	m_frontLeftSolenoid(0, 1),
	m_frontRightSolenoid(0, 1),
	m_backRightSolenoid(0, 1),
	m_backLeftSolenoid(0, 1),
	m_cubeRotatorMotor(1), //TODO fill these motors in with actual ports that we are going to be using
	m_leftArmMotor(2),
	m_rightArmMotor(3) {
	m_liftArmPosition = 0;

}

void ScorerSubsystem::robotInit() {
	Robot->m_operatorJoystick.registerButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
	Robot->m_operatorJoystick.registerButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER);
	Robot->m_operatorJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y);
}

void ScorerSubsystem::autonInit() {

}

void ScorerSubsystem::auton() {

}

void ScorerSubsystem::teleopInit() {

}

void ScorerSubsystem::teleop() {

}

void ScorerSubsystem::rotateCube() {
	if (m_isArmGoingUp == false && Robot->m_operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y) >= 0.1) {

		m_leftArmMotor.Set(ControlMode::PercentOutput, Robot->m_operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y));
		m_rightArmMotor.Set(ControlMode::PercentOutput, Robot->m_operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y));
		m_isArmGoingUp = true;
	}

}

void ScorerSubsystem::intakeCube() {
	if (m_intakeIsClosed == false && Robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER) == true){
		m_frontLeftSolenoid.Set(DoubleSolenoid::kForward);
		m_frontRightSolenoid.Set(DoubleSolenoid::kForward);
		m_backLeftSolenoid.Set(DoubleSolenoid::kForward);
		m_backRightSolenoid.Set(DoubleSolenoid::kForward);
		m_intakeIsClosed = true;
	}
}

void ScorerSubsystem::outakeCube() {
	if (m_intakeIsClosed == true && Robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER) == true) {
		m_frontLeftSolenoid.Set(DoubleSolenoid::kReverse);
		m_frontRightSolenoid.Set(DoubleSolenoid::kReverse);
		m_backLeftSolenoid.Set(DoubleSolenoid::kReverse);
		m_backRightSolenoid.Set(DoubleSolenoid::kReverse);
		m_intakeIsClosed = false;
	}
}


