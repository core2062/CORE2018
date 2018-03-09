#include "ScorerSubsystem.h"
#include "COREFramework/COREScheduler.h"
#include "ctre/Phoenix.h"
#include <WPILib.h>

#include "Robot.h"

ScorerSubsystem::ScorerSubsystem() :
		m_scorerSolenoid(SCORER_IN_SOLENOID_PORT, SCORER_OUT_SOLENOID_PORT) {

}

void ScorerSubsystem::robotInit() {
	operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
	openScorer();
	m_scorerClosed = false;
}

void ScorerSubsystem::teleopInit() {
}

void ScorerSubsystem::teleop() {
	if (operatorJoystick->getRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
		if(m_scorerClosed) {
			openScorer();
		} else {
			closeScorer();
		}
		m_scorerClosed = ! m_scorerClosed;
	}
	if (operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
		intakeCube();
	}
	if (operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER)) {
		outakeCube();
	}
}

void ScorerSubsystem::closeScorer() {
	m_scorerSolenoid.Set(DoubleSolenoid::kForward);
}

void ScorerSubsystem::openScorer() {
	m_scorerSolenoid.Set(DoubleSolenoid::kReverse);
}

void ScorerSubsystem::outakeCube() {
	m_frontLeftSolenoid.Set(DoubleSolenoid::kReverse);
	m_frontRightSolenoid.Set(DoubleSolenoid::kReverse);
	m_backLeftSolenoid.Set(DoubleSolenoid::kReverse);
	m_backRightSolenoid.Set(DoubleSolenoid::kReverse);
}
