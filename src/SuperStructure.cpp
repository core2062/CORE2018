#include "SuperStructure.h"

#include "Robot.h"

SuperStructure::SuperStructure():
        m_liftCubeClearanceHeight("Lift No Cube Safe Height") {
}

void SuperStructure::robotInitTask() {
    m_liftSubsystem = &CORE2018::GetInstance()->liftSubsystem;
    m_chainBarSubsytem = &CORE2018::GetInstance()->chainBarSubsystem;
    m_scorerSubsystem = &CORE2018::GetInstance()->scorerSubsystem;
    m_grabCubeState = GrabCubeState::WAITING_FOR_CUBE;
}

void SuperStructure::postLoopTask() {
    SystemState newState = m_systemState;
    switch (m_systemState) {
        case SystemState::TRANSIT_BELOW_CHANGE_POINT:
        	newState = transitBelowChangePoint();
            break;
        case SystemState::TRANSIT_ABOVE_CHANGE_POINT:
        	newState = transitAboveChangePoint;
            break;
        case SystemState::GRABBING_CUBE:
            newState = handleGrabbingCube();
            break;
        case SystemState::SWITCH_SCORING:
            break;
        case SystemState::SCALE_SCORING:
            break;
        case SystemState::SCALE_BEHIND_SCORING:
            break;
        case SystemState::CHAINBAR_STRAIGHT_UP:
        	newState = chainBarStraightUp();
            break;
    }

    if(newState != m_systemState) {
        CORELog::logInfo("Changing states from " + to_string((int)m_systemState) + " to " + to_string((int)newState));
        m_systemState = newState;
    }
}

void SuperStructure::setWantedState(WantedState wantedState) {
    m_wantedState = wantedState;
}

SuperStructure::SystemState SuperStructure::scaleScoring() {
	switch(m_scaleScoreState) {
	case ScaleScoreState::HIGH_SCALE:
		//Need to set chainbar to necessary angle
		m_liftSubsystem->SetScaleHighHeight();
		m_chainBarSubsystem->SetForwardRotation();
		m_scorerSubsystem->openScorer();
		break;
	case ScaleScoreState::MID_SCALE:
		//Need to set chainbar to necessary angle
		m_liftSubsystem->SetScaleMediumHeight();
		m_chainBarSubsystem->SetForwardRotation();
		m_scorerSubsystem->openScorer();
		break;
	case ScaleScoreState::LOW_SCALE:
		//Need to set chainbar to necessary angle
		m_liftSubsystem->SetScaleLowHeight();
		m_chainBarSubsystem->SetForwardRotation();
		m_scorerSubsystem->openScorer();
		break;
	}
	return SystemState::SCALE_SCORING;
}

SuperStructure::SystemState SuperStructure::behindScaleScoring() {
	switch(m_scaleScoreState) {
	case ScaleScoreState::HIGH_SCALE:
		//Need to set chainbar to necessary angle for scoring backwards
		m_liftSubsystem->SetScaleHighHeight();
		m_chainBarSubsystem->SetBackwardsRotation();
		m_scorerSubsystem->openScorer();
		break;
	case ScaleScoreState::MID_SCALE:
		//Need to set chainbar to necessary angle for scoring backwards
		m_liftSubsystem->SetScaleMediumHeight();
		m_chainBarSubsystem->SetBackwardsRotation();
		m_scorerSubsystem->openScorer();
		break;
	case ScaleScoreState::LOW_SCALE:
		//Need to set chainbar to necessary angle for scoring backwards
		m_liftSubsystem->SetScaleLowHeight();
		m_chainBarSubsystem->SetBackwardsRotation();
		m_scorerSubsystem->openScorer();
		break;
	}
	switch (m_wantedState) {

	}
	return SystemState::SCALE_BEHIND_SCORING;

}
SuperStructure::SystemState SuperStructure::switchScoring() {
	m_liftSubsystem->SetSwitchHeight();
	m_chainBarSubsystem->SetForwardRotation();
	m_scorerSubsystem->openScorer();
	switch (m_wantedState) {
	}
	return SystemState::SWITCH_SCORING;
}

SuperStructure::SystemState SuperStructure::transitAboveChangePoint() {
	m_liftSubsystem->SetTransitAboveChangeHeight();
}

SuperStructure::SystemState SuperStructure::transitBelowChangePoint() {
	m_liftSubsystem->SetTransitBelowChangeHeight();
}

SuperStructure::SystemState SuperStructure::chainBarStraightUp() {
	m_chainBarSubsystem->SetChainBarStraightUp();
}

SuperStructure::SystemState SuperStructure::handleGrabbingCube() {
    m_chainBarSubsytem->SetIntakePosition(); //Set chain bar + rotation to correct angles
    switch (m_grabCubeState) {
        case GrabCubeState::WAITING_FOR_CUBE:
            m_liftSubsystem->SetSafeHeight(); //Set lift position to clearance height above cube
            m_scorerSubsystem->openScorer();
            if(m_scorerSubsystem->cubeInScorer()) {
                m_grabCubeState = GrabCubeState::MOVING_DOWN_TO_CUBE;
            }
            break;
        case GrabCubeState::MOVING_DOWN_TO_CUBE:
            m_liftSubsystem->SetRequestedPosition(0); //Set lift position to 0
            if(m_liftSubsystem->liftDown()) {
                m_scorerSubsystem->closeScorer();
                m_grabCubeState = GrabCubeState::MOVING_UP_TO_CUBE_CLEARANCE;
            }
            break;
        case GrabCubeState::MOVING_UP_TO_CUBE_CLEARANCE:
            m_liftSubsystem->SetCubeClearanceHeight();
            if(m_liftSubsystem->IsAboveCubeClearanceHeight()) { //Lift higher than safe height
                m_grabCubeState = GrabCubeState::CUBE_CLEARANCE_HIEGHT;
            }
            break;
        case GrabCubeState::CUBE_CLEARANCE_HIEGHT:
            m_liftSubsystem->SetCubeClearanceHeight();
            break;
    }

    switch (m_wantedState) { //Figure out new system state
        case WantedState::WANT_TO_PICKUP_CUBE:
            //May want to set state to straight up here if in cube safe hieght with cube
            return SystemState::GRABBING_CUBE;
        default:
            if(m_grabCubeState == GrabCubeState::CUBE_CLEARANCE_HIEGHT
               || m_grabCubeState == GrabCubeState::WAITING_FOR_CUBE) {
                return SystemState::TRANSIT;
            } else {
                m_grabCubeState = GrabCubeState::MOVING_UP_TO_CUBE_CLEARANCE;
                return SystemState::GRABBING_CUBE;
            }
    }
}

/*SuperStructure::SystemState SuperStructure::handleTransit() {
    switch (m_wantedState) {
        case WantedState::WANT_TO_PICKUP_CUBE:
            return SystemState::GRABBING_CUBE;
        default:
            return SystemState::TRANSIT;
    }
}*/

