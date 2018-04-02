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
    return COREAutonAction::actionStatus::END;
}

void ScorerAction::actionEnd() {

}
