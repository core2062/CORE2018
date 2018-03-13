#include <Autonomous/Action/ScorerAction.h>

#include "Robot.h"

ScorerAction::ScorerAction(scorerAction action) {
	m_requestedAction = action;
}

void ScorerAction::actionInit() {
	switch(m_requestedAction) {
		case OPEN:
			CORE2018::GetInstance()->scorerSubsystem.openScorer();
			break;
		case CLOSED:
			CORE2018::GetInstance()->scorerSubsystem.closeScorer();
			break;
		default:
			break;
	}
}

COREAutonAction::actionStatus ScorerAction::action() {
	if(m_requestedAction == WAIT_FOR_CUBE) {
		//TODO: add code here that will keep action looping until cube is detected in scorer, at which point the scorer will close and the action ended.
		return COREAutonAction::actionStatus::CONTINUE;
	} else {
		return COREAutonAction::actionStatus::END;
	}
}
void ScorerAction::actionEnd() {

}
