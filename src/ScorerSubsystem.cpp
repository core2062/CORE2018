#include "ScorerSubsystem.h"
#include "COREFramework/COREScheduler.h"
#include "ctre/Phoenix.h"
#include <WPILib.h>

#include "Robot.h"

ScorerSubsystem::ScorerSubsystem() :
		m_scorerSolenoid(SCORER_IN_SOLENOID_PORT, SCORER_OUT_SOLENOID_PORT) {
    m_buttonPressed = false;
}

void ScorerSubsystem::robotInit() {
	operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER);
	openScorer();
	m_scorerClosed = false;
}

void ScorerSubsystem::teleopInit() {
}

void ScorerSubsystem::teleop() {
	if (operatorJoystick->m_joystick.GetRawButton(1)) {
        closeScorer();
	} else {
        openScorer();
    }
}

void ScorerSubsystem::closeScorer() {
	m_scorerSolenoid.Set(DoubleSolenoid::kForward);
    CORELog::logInfo("Closing");
}

void ScorerSubsystem::openScorer() {
	m_scorerSolenoid.Set(DoubleSolenoid::kReverse);
    CORELog::logInfo("Opening");

}
