#include "ScorerSubsystem.h"

#include "Robot.h"

ScorerSubsystem::ScorerSubsystem() :
		m_scorerSolenoid(SCORER_IN_SOLENOID_PORT, SCORER_OUT_SOLENOID_PORT),
        m_photoEye(PHOTOEYE_PORT) {
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
	m_scorerSolenoid.Set(DoubleSolenoid::kReverse);
    CORELog::logInfo("Closing");
}

void ScorerSubsystem::openScorer() {
	m_scorerSolenoid.Set(DoubleSolenoid::kForward);
    CORELog::logInfo("Opening");

}

bool ScorerSubsystem::cubeInScorer() {
    return !m_photoEye.Get();
}
