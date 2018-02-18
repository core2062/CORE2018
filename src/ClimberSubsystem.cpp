#include <ClimberSubsystem.h>

// TODO fill the motor in with an actual motor instead of 0
ClimberSubsystem::ClimberSubsystem(COREJoystick * operatorJoystick) :
		m_climbMotor(0) {
	m_operatorJoystick = operatorJoystick;
}

void ClimberSubsystem::robotInit() {
	m_operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::START_BUTTON);
}

void ClimberSubsystem::teleopInit() {
	m_climbMotor.Set(ControlMode::PercentOutput, 0);
}

void ClimberSubsystem::teleop() {
	if (m_operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::START_BUTTON)) {
		startClimbing();
	} else {
		stopClimbing();
	}
}


void ClimberSubsystem::startClimbing() {
	m_climbMotor.Set(ControlMode::PercentOutput, 0.2);
}

void ClimberSubsystem::stopClimbing() {
	m_climbMotor.Set(ControlMode::PercentOutput, 0);
}
