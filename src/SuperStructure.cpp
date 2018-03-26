#include "SuperStructure.h"

#include "Robot.h"

SuperStructure::SuperStructure() {
    m_liftSubsystem = &CORE2018::GetInstance()->liftSubsystem;
    m_chainBarSubsytem = &CORE2018::GetInstance()->chainBarSubsystem;
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
            break;
        case SystemState::SCALE_SCORING:
            break;
        case SystemState::SCALE_BEHIND_SCORING:
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

SuperStructure::SystemState SuperStructure::handleGrabbingCube() {
    //Set chain bar + rotation to correct angles
    switch (m_grabCubeState) {
        case GrabCubeState::WAITING_FOR_CUBE:
            //Set lift position to clearance height above cube
            if(m_scorerSubsystem->cubeInScorer()) {
                m_grabCubeState = GrabCubeState::MOVING_DOWN_TO_CUBE;
            }
            break;
        case GrabCubeState::MOVING_DOWN_TO_CUBE:
            //Set lift position to 0
            if(m_liftSubsystem->liftDown() && m_scorerSubsystem->cubeInScorer()) {
                m_scorerSubsystem->closeScorer();
                m_grabCubeState = GrabCubeState::MOVING_UP_TO_SAFE;
            }
            break;
        case GrabCubeState::MOVING_UP_TO_SAFE:
            //Set lift position to cube safe hieght
            if(m_liftSubsystem->GetLiftInches() > 0) { //Lift higher than safe hieght
                m_grabCubeState = GrabCubeState::CUBE_SAFE_HIEGHT;
            }
            break;
        case GrabCubeState::CUBE_SAFE_HIEGHT:
            //Set lift position to cube safe hieght
            break;
    }

    switch (m_wantedState) { //Figure out new system state
        case WantedState::WANT_TO_PICKUP_CUBE:
            //May want to set state to straight up here if in cube safe hieght with cube
            return SystemState::GRABBING_CUBE;
        default:
            if(m_grabCubeState == GrabCubeState::CUBE_SAFE_HIEGHT) {
                return SystemState::TRANSIT_BELOW_CHANGE_POINT;
            } else {
                m_grabCubeState = GrabCubeState::MOVING_UP_TO_SAFE;
                return SystemState::GRABBING_CUBE;
            }
    }
}
