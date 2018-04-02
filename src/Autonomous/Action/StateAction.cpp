#include <Robot.h>
#include "StateAction.h"

StateAction::StateAction(WantedState wantedState) {
    m_requestedState = wantedState;
}

void StateAction::actionInit() {
    CORE2018::GetInstance()->superStructure.setWantedState(m_requestedState);
}

COREAutonAction::actionStatus StateAction::action() {
    return END;
}

void StateAction::actionEnd() {

}
