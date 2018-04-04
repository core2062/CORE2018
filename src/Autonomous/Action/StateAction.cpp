#include <Robot.h>
#include "StateAction.h"
#include "SuperStructure.h"

StateAction::StateAction(WantedState wantedState, WantedScaleScoreHeight wantedScoreHieght) {
    m_requestedState = wantedState;
    m_wantedScaleScoreHeight = wantedScoreHieght;
}

void StateAction::actionInit() {
    CORE2018::GetInstance()->superStructure.setWantedState(m_requestedState);
    CORE2018::GetInstance()->superStructure.setWantedScaleScoreHeight(m_wantedScaleScoreHeight);
}

COREAutonAction::actionStatus StateAction::action() {
	switch(m_requestedState) {
	case WantedState::WANT_TO_PICKUP_CUBE:
		switch(m_actualState) {
		case SystemState::GRABBING_CUBE:
			return END;
			break;
		default:
			break;
		}
	case WantedState::WANT_TO_BE_STRAIGHT_UP:
		switch(m_actualState) {
			case SystemState::STRAIGHT_UP: {
				return END;
				break;
			}
			default:
				break;
		}
	case WantedState::WANT_TO_GET_FROM_FEEDER:
		switch(m_actualState) {
			case SystemState::FEEDER:
				return END;
				break;
			default:
				break;

		}
	case WantedState::WANT_TO_SCORE_ON_SCALE:
		switch(m_actualState) {
			case SystemState::SCALE_SCORING:
				return END;
				break;
			default:
				break;
		}
	case WantedState::WANT_TO_SCORE_ON_SCALE_BEHIND:
		switch(m_actualState) {
			case SystemState::SCALE_BEHIND_SCORING:
				return END;
				break;
			default:
				break;
		}
	case WantedState::WANT_TO_SCORE_ON_SWITCH:
		switch(m_actualState) {
			case SystemState::SWITCH_SCORING:
				return END;
				break;
			default:
				break;
		}
	case WantedState::MANUAL:
		switch(m_actualState) {
			case SystemState::TRANSIT:
				return END;
			default:
				break;

		}
	default:
		return CONTINUE;
	}
}

void StateAction::actionEnd() {

}
