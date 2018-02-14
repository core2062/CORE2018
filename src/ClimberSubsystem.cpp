#include <ClimberSubsystem.h>
ClimberSubsystem::ClimberSubsystem() : m_climbMotor(0) {
	m_isClimbing = false;
}
void ClimberSubsystem::robotInit() {
	m_climbMotor.Set(ControlMode::PercentOutput, 0);
	robot->m_operatorJoystick.registerButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER);
	robot->m_operatorJoystick.registerButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);

	//m_stick.GetRawButton(0);
}
void ClimberSubsystem::teleopInit() {
	m_isClimbing = false;
	//m_stick.GetButton(Joystick::kTriggerButton);
}
void ClimberSubsystem::teleop() {

}
bool ClimberSubsystem::isClimbing () {
	return m_isClimbing;
}
void ClimberSubsystem::startClimbing () {
	if (m_isClimbing == false && robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER) == true) {
		m_climbMotor.Set(ControlMode::PercentOutput, 0.2);
		m_isClimbing = true;
	}

}
void ClimberSubsystem::stopClimbing () {
	if (m_isClimbing == true && robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER) == false) {
		m_climbMotor.Set(ControlMode::PercentOutput, 0);
		m_isClimbing = false;
	}

}
