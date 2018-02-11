/*#include <ClimberSubsystem.h>

ClimberSubsystem::ClimberSubsystem() : m_climbMotor(0) {
	m_isClimbing = false;
}
void ClimberSubsystem::robotInit() {
	m_climbMotor.Set(ControlMode::PercentOutput, 0);
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
	if (m_isClimbing == false && m_stick.GetRawButtonPressed(0) == true) {
		m_climbMotor.Set(ControlMode::PercentOutput, 0.2);
		m_isClimbing = true;
	}

}
void ClimberSubsystem::stopClimbing () {
	if (m_isClimbing == true && m_stick.GetRawButtonPressed(0) == false) {
		m_climbMotor.Set(ControlMode::PercentOutput, 0);
		m_isClimbing = false;
	}

}
*/

