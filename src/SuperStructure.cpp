#include "SuperStructure.h"

#include "Robot.h"

SuperStructure::SuperStructure() {
    m_liftSubsystem = &CORE2018::GetInstance()->liftSubsystem;
    m_chainBarSubsystem = &CORE2018::GetInstance()->chainBarSubsystem;
    m_scorerSubsystem = &CORE2018::GetInstance()->scorerSubsystem;
}

void SuperStructure::robotInit() {

}

void SuperStructure::postLoopTask() {
    SystemState newState = m_systemState;
    switch (m_systemState) {
        case SystemState::TRANSIT_BELOW_CHANGE_POINT:
            break;
        case SystemState::TRANSIT_ABOVE_CHANGE_POINT:
            break;
        case SystemState::GRABBING_CUBE:
            newState = handleGrabbingCube();
            break;
        case SystemState::SWITCH_SCORING:
        	newState = switchScoring();
            break;
        case SystemState::SCALE_SCORING:
        	newState = scaleScoring();
            break;
        case SystemState::SCALE_BEHIND_SCORING:
        	newState = behindScaleScoring();
            break;
        case SystemState::STRAIGHT_UP:
            break;
    }

    if(newState != m_systemState) {
        CORELog::logInfo("Changing states from " + to_string((int)m_systemState) + " to " + to_string((int)newState));
        m_systemState = newState;
    }
}

void SuperStructure::setWantedState(SuperStructure::WantedState wantedState) {
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
	return SystemState::SCALE_BEHIND_SCORING;

}
SuperStructure::SystemState SuperStructure::switchScoring() {
	m_liftSubsystem->SetSwitchHeight();
	m_chainBarSubsystem->SetForwardRotation();
	m_scorerSubsystem->openScorer();
	return SystemState::SWITCH_SCORING;
}

SuperStructure::SystemState SuperStructure::handleGrabbingCube() {
    //Set chain bar + rotation to correct angles
    switch (m_grabCubeState) {
        case GrabCubeState::WAITING_FOR_CUBE:
        	m_liftSubsystem->SetCubeClearanceHeight();
            //Set lift position to clearance height above cube
            if(m_scorerSubsystem->cubeInScorer()) {
                m_grabCubeState = GrabCubeState::MOVING_DOWN_TO_CUBE;
            }
            break;
        case GrabCubeState::MOVING_DOWN_TO_CUBE:
            //Set lift position to 0
        	m_liftSubsystem->SetRequestedPosition(0);
            if(m_liftSubsystem->liftDown() && m_scorerSubsystem->cubeInScorer()) {
                m_scorerSubsystem->closeScorer();
                m_grabCubeState = GrabCubeState::MOVING_UP_TO_SAFE;
            }
            break;
        case GrabCubeState::MOVING_UP_TO_SAFE:
            //Set lift position to cube safe height
        	m_liftSubsystem->SetCubeSafeHeight();
            if(m_liftSubsystem->GetLiftInches() > 0) { //Lift higher than safe height
            	m_liftSubsystem->SetCubeAboveSafeHeight();
            	//Adds five inches to the safe lift position
                m_grabCubeState = GrabCubeState::CUBE_SAFE_HEIGHT;
            }
            break;
        case GrabCubeState::CUBE_SAFE_HEIGHT:
        	m_liftSubsystem->SetCubeSafeHeight();
            //Set lift position to cube safe height
            break;
    }

    switch (m_wantedState) { //Figure out new system state
        case WantedState::WANT_TO_PICKUP_CUBE:
            //May want to set state to straight up here if in cube safe height with cube
            return SystemState::GRABBING_CUBE;
        default:
            if(m_grabCubeState == GrabCubeState::CUBE_SAFE_HEIGHT) {
                return SystemState::TRANSIT_BELOW_CHANGE_POINT;
            } else {
                m_grabCubeState = GrabCubeState::MOVING_UP_TO_SAFE;
                return SystemState::GRABBING_CUBE;
            }
    }
}
