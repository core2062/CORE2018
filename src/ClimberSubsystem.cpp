#include <ClimberSubsystem.h>

ClimberSubsystem::ClimberSubsystem() : //TODO fill the motor in with an actual motor instead of 0
	m_climbMotor(0) {
		m_isClimbing = false;
	}
void ClimberSubsystem::robotInit() {
	m_climbMotor.Set(ControlMode::PercentOutput, 0);
	Robot->m_operatorJoystick.registerButton(CORE::COREJoystick::JoystickButton::START_BUTTON);
}
void ClimberSubsystem::teleopInit() {
	m_isClimbing = false;
}
void ClimberSubsystem::teleop() {

}
bool ClimberSubsystem::isClimbing () {
	return m_isClimbing;
}
void ClimberSubsystem::startClimbing () {
	if (m_isClimbing == false && Robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::START_BUTTON) == true) {
		m_climbMotor.Set(ControlMode::PercentOutput, 0.2);
		m_isClimbing = true;
	}

}
void ClimberSubsystem::stopClimbing () {
	if (m_isClimbing == true && Robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::START_BUTTON) == false) {
		m_climbMotor.Set(ControlMode::PercentOutput, 0);
		m_isClimbing = false;
	}

}
