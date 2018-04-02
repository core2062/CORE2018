#include "SuperStructure.h"
#include "COREUtilities/COREConstant.h"
#include "Robot.h"

SuperStructure::SuperStructure():
        m_transitTransitionTimeout("Transit Transition Timeout"),
        m_grabCubeTimeout("Grab Cube Timeout") {

}

void SuperStructure::robotInitTask() {
    m_liftSubsystem = &CORE2018::GetInstance()->liftSubsystem;
    m_chainBarSubsystem = &CORE2018::GetInstance()->chainBarSubsystem;
    m_scorerSubsystem = &CORE2018::GetInstance()->scorerSubsystem;
}

void SuperStructure::teleopInitTask() {
    m_grabCubeState = GrabCubeState::WAITING_FOR_CUBE;
    m_cubeTimerStarted = false;
    m_wantedState = WantedState::MANUAL;
    m_systemState = SystemState::TRANSIT;
    m_timeoutTimer.Reset();
    m_timeoutTimer.Start();
}

void SuperStructure::postLoopTask() {
    SystemState newState = m_systemState;
    switch (m_systemState) {
        case SystemState::TRANSIT:
            newState = handleTransit();
            break;
        case SystemState::GRABBING_CUBE:
            newState = handleGrabbingCube();
            break;
        case SystemState::SWITCH_SCORING:
            newState = handleSwitchScoring();
            break;
        case SystemState::SCALE_SCORING:
            newState = handleScaleScoring();
            break;
        case SystemState::SCALE_BEHIND_SCORING:
            newState = handleBehindScaleScoring();
            break;
        case SystemState::STRAIGHT_UP:
            newState = handleStraightUp();
            break;
        case SystemState::FEEDER:
            newState = handleFeeder();
            break;
    }

    if(newState != m_systemState) {
        CORELog::logInfo("Changing states from " + to_string((int)m_systemState) + " to " + to_string((int)newState));
        m_systemState = newState;
        m_timeoutTimer.Reset();
        m_timeoutTimer.Start();
    }
}

void SuperStructure::setWantedState(WantedState wantedState) {
    m_wantedState = wantedState;
    if(m_wantedState == WantedState::WANT_TO_PICKUP_CUBE) {
        m_grabCubeState = GrabCubeState::WAITING_FOR_CUBE;
    }
}

void SuperStructure::setWantedScaleScoreHeight(WantedScaleScoreHeight wantedHeight) {
    m_wantedScaleScoreHeight = wantedHeight;
}

SuperStructure::SystemState SuperStructure::handleTransit() {
    bool reachedTarget = false;
    switch (m_wantedState) {
        case WantedState::WANT_TO_PICKUP_CUBE:
            m_chainBarSubsystem->SetIntakePosition();
            m_liftSubsystem->SetSafeHeight();
            m_scorerSubsystem->openScorer();
            reachedTarget = m_chainBarSubsystem->IsIntakePosition();
            break;
        case WantedState::WANT_TO_SCORE_ON_SCALE:
            m_chainBarSubsystem->SetForwardScore();
            m_scorerSubsystem->closeScorer();
            switch (m_wantedScaleScoreHeight) {
                case WantedScaleScoreHeight::HIGH_SCALE:
                    m_liftSubsystem->SetScaleHighHeight();
                    reachedTarget = m_liftSubsystem->IsScaleHighHeight();
                    break;
                case WantedScaleScoreHeight::MID_SCALE:
                    m_liftSubsystem->SetScaleMediumHeight();
                    reachedTarget = m_liftSubsystem->IsScaleMediumHeight();
                    break;
            }
            break;
        case WantedState::WANT_TO_SCORE_ON_SCALE_BEHIND:
            m_chainBarSubsystem->SetBehindScore();
            m_scorerSubsystem->closeScorer();
            switch (m_wantedScaleScoreHeight) {
                case WantedScaleScoreHeight::HIGH_SCALE:
                    m_liftSubsystem->SetScaleHighHeight();
                    reachedTarget = m_liftSubsystem->IsScaleHighHeight();
                    break;
                case WantedScaleScoreHeight::MID_SCALE:
                    m_liftSubsystem->SetScaleMediumHeight();
                    reachedTarget = m_liftSubsystem->IsScaleMediumHeight();
                    break;
            }
            break;
        case WantedState::WANT_TO_SCORE_ON_SWITCH:
            m_chainBarSubsystem->SetForwardScore();
            if(m_scorerSubsystem->cubeInScorer()) {
                m_scorerSubsystem->closeScorer();
            }
            reachedTarget = m_chainBarSubsystem->IsForwardScore();
            break;
        case WantedState::WANT_TO_GET_FROM_FEEDER: //TODO: I'm lazy. Make this more like above cases
            m_chainBarSubsystem->SetFeeder();
            m_liftSubsystem->SetRequestedPosition(0);
            m_scorerSubsystem->openScorer();
            reachedTarget = m_liftSubsystem->liftDown();
            break;
        case WantedState::WANT_TO_BE_STRAIGHT_UP:
            m_chainBarSubsystem->SetStraightUp();
            reachedTarget = m_chainBarSubsystem->IsStraightUp();; //TODO: There should probably be a condition here
            break;
        case WantedState::MANUAL:
            break;
    }

    reachedTarget = reachedTarget || m_timeoutTimer.Get() > m_transitTransitionTimeout.Get();

    CORELog::logInfo("Wanted State: " + to_string((int)m_wantedState) + " System State: " +
                             to_string((int)m_systemState) + " Target Reached: " + to_string(reachedTarget));

    //State transition
    switch (m_wantedState) {
        case WantedState::WANT_TO_PICKUP_CUBE:
            if(reachedTarget) {
                m_grabCubeState = GrabCubeState::WAITING_FOR_CUBE;
                m_cubeTimerStarted = false;
                return SystemState::GRABBING_CUBE;
            } else {
                return SystemState::TRANSIT;
            }
        case WantedState::WANT_TO_SCORE_ON_SCALE:
            if (reachedTarget) {
                return SystemState::SCALE_SCORING;
            } else {
                return SystemState::TRANSIT;
            }
        case WantedState::WANT_TO_SCORE_ON_SCALE_BEHIND:
            if (reachedTarget) {
                return SystemState::SCALE_BEHIND_SCORING;
            } else {
                return SystemState::TRANSIT;
            }
        case WantedState::WANT_TO_SCORE_ON_SWITCH:
            if (reachedTarget) {
                return SystemState::SWITCH_SCORING;
            } else {
                return SystemState::TRANSIT;
            }
        case WantedState::WANT_TO_GET_FROM_FEEDER:
            if (reachedTarget) {
                return SystemState::FEEDER;
            } else {
                return SystemState::TRANSIT;
            }
        case WantedState::WANT_TO_BE_STRAIGHT_UP:
            if (reachedTarget) {
                return SystemState::STRAIGHT_UP;
            } else {
                return SystemState::TRANSIT;
            }
        case WantedState::MANUAL:
            return SystemState::TRANSIT;
    }

}

SuperStructure::SystemState SuperStructure::handleGrabbingCube() {
    m_chainBarSubsystem->SetIntakePosition(); //Set chain bar + rotation to correct angles
    switch (m_grabCubeState) {
        case GrabCubeState::WAITING_FOR_CUBE:
            m_liftSubsystem->SetSafeHeight(); //Set lift position to clearance height above cube
            m_scorerSubsystem->openScorer();
            if (m_scorerSubsystem->cubeInScorer() && !m_cubeTimerStarted) {
                m_cubeTimer.Reset();
                m_cubeTimer.Start();
                m_cubeTimerStarted = true;
            }
            if(m_cubeTimerStarted && m_cubeTimer.Get() > 0.5) {
                m_cubeTimerStarted = false;
                m_timeoutTimer.Reset();
                m_timeoutTimer.Start();
                m_grabCubeState = GrabCubeState::MOVING_DOWN_TO_CUBE;
            }
            break;
        case GrabCubeState::MOVING_DOWN_TO_CUBE:
            m_liftSubsystem->SetRequestedPosition(0); //Set lift position to 0
            if (m_liftSubsystem->liftDown() || m_timeoutTimer.Get() > m_grabCubeTimeout.Get()) {
                m_scorerSubsystem->closeScorer();
                m_timeoutTimer.Reset();
                m_timeoutTimer.Start();
                m_grabCubeState = GrabCubeState::MOVING_UP_TO_CUBE_CLEARANCE;
            } else {
                m_scorerSubsystem->openScorer();
            }
            break;
        case GrabCubeState::MOVING_UP_TO_CUBE_CLEARANCE:
            m_liftSubsystem->SetCubeClearanceHeight();
            if (m_liftSubsystem->IsAboveCubeClearanceHeight()
                || m_timeoutTimer.Get() > m_grabCubeTimeout.Get()) { //Lift is higher than cube clearance height
                m_grabCubeState = GrabCubeState::CUBE_CLEARANCE_HEIGHT;
            }
            break;
        case GrabCubeState::CUBE_CLEARANCE_HEIGHT:
            m_liftSubsystem->SetCubeClearanceHeight();
            break;
    }

    switch (m_wantedState) { //Figure out new system state
        case WantedState::WANT_TO_PICKUP_CUBE:
            //May want to set state to straight up here if in cube safe hieght with cube
            return SystemState::GRABBING_CUBE;
        default:
            if (m_grabCubeState == GrabCubeState::CUBE_CLEARANCE_HEIGHT) {
                return SystemState::TRANSIT;
            } else {
                m_grabCubeState = GrabCubeState::MOVING_UP_TO_CUBE_CLEARANCE;
                return SystemState::GRABBING_CUBE;
            }
    }
}

SuperStructure::SystemState SuperStructure::handleSwitchScoring() {
    m_liftSubsystem->SetSwitchHeight();
    m_chainBarSubsystem->SetForwardScore();
    switch (m_wantedState) {
        case WantedState::WANT_TO_SCORE_ON_SWITCH:
            return SystemState::SWITCH_SCORING;
        default:
            return SystemState::TRANSIT;
    }
}

SuperStructure::SystemState SuperStructure::handleScaleScoring() {
    switch (m_wantedScaleScoreHeight) {
        case WantedScaleScoreHeight::HIGH_SCALE:
            m_liftSubsystem->SetScaleHighHeight();
            break;
        case WantedScaleScoreHeight::MID_SCALE:
            m_liftSubsystem->SetScaleMediumHeight();
            break;
    }
    m_chainBarSubsystem->SetForwardScore();
    switch (m_wantedState) {
        case WantedState::WANT_TO_SCORE_ON_SCALE:
            return SystemState::SCALE_SCORING;
        default:
            return SystemState::TRANSIT;
    }
}

SuperStructure::SystemState SuperStructure::handleBehindScaleScoring() {
    switch (m_wantedScaleScoreHeight) {
        case WantedScaleScoreHeight::HIGH_SCALE:
            m_liftSubsystem->SetScaleHighHeight();
            break;
        case WantedScaleScoreHeight::MID_SCALE:
            m_liftSubsystem->SetScaleMediumHeight();
            break;
    }
    m_chainBarSubsystem->SetBehindScore();
    switch (m_wantedState) {
        case WantedState::WANT_TO_SCORE_ON_SCALE_BEHIND:
            return SystemState::SCALE_BEHIND_SCORING;
        default:
            return SystemState::TRANSIT;
    }
}

SuperStructure::SystemState SuperStructure::handleFeeder() {
    m_liftSubsystem->SetRequestedPosition(0); //TODO: I'm still lazy. Make this more like above cases
    m_chainBarSubsystem->SetFeeder();
    switch (m_wantedState) {
        case WantedState::WANT_TO_GET_FROM_FEEDER:
            return SystemState::FEEDER;
        default:
            return SystemState::TRANSIT;
    }
}

SuperStructure::SystemState SuperStructure::handleStraightUp(){
    m_chainBarSubsystem->SetStraightUp();
    m_liftSubsystem->SetRequestedPosition(0);
    switch (m_wantedState) {
        case WantedState::WANT_TO_BE_STRAIGHT_UP:
            return SystemState::STRAIGHT_UP;
        default:
            return SystemState::TRANSIT;
    }
}
