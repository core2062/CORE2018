#include "ScorerSubsystem.h"
#include "COREFramework/COREScheduler.h"
#include "ctre/Phoenix.h"
#include "CORELogging/CORELog.h"
#include <WPILib.h>

#include "Robot.h"

ScorerSubsystem::ScorerSubsystem() :
		m_scorerSolenoid(SCORER_IN_SOLENOID_PORT, SCORER_OUT_SOLENOID_PORT) {
    m_scorerClosed = false;
}

void ScorerSubsystem::robotInit() {
	operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
	openScorer();
}

void ScorerSubsystem::teleopInit() {

}

void ScorerSubsystem::teleop() {
	if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
        if(m_scorerClosed) {
            openScorer();
        } else {
            closeScorer();
        }
        m_scorerClosed = !m_scorerClosed;
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
