#include <Robot.h>
#include "StateAction.h"

StateAction::StateAction(WantedState wantedState, WantedScaleScoreHeight wantedScoreHieght) {
    m_requestedState = wantedState;
    m_wantedScaleScoreHeight = wantedScoreHieght;
}

void StateAction::actionInit() {
    CORE2018::GetInstance()->superStructure.setWantedState(m_requestedState);
    CORE2018::GetInstance()->superStructure.setWantedScaleScoreHeight(m_wantedScaleScoreHeight);
}

COREAutonAction::actionStatus StateAction::action() {
    return END;
}

void StateAction::actionEnd() {

}
