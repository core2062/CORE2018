#pragma once

#include <CORERobotLib.h>
#include "LiftSubsystem.h"
#include "ScorerSubsystem.h"
#include "ChainBarSubsystem.h"
#include "COREUtilities/COREConstant.h"
#include "COREFramework/COREScheduler.h"

using namespace CORE;

enum class WantedState {
    WANT_TO_PICKUP_CUBE, //We want to pickup a cube
    WANT_TO_SCORE_ON_SCALE, //We want to score on the scale
    WANT_TO_SCORE_ON_SCALE_BEHIND, //We want to score on the scale, but behind us
    WANT_TO_SCORE_ON_SWITCH, //We want to score on the switch
    WANT_TO_GET_FROM_FEEDER, //We want to get from the feeder
    WANT_TO_BE_STRAIGHT_UP, //We want to be straight up for best center of gravity
    MANUAL //We want manual control
};

enum class SystemState {
        TRANSIT,
        GRABBING_CUBE,
        SWITCH_SCORING,
        SCALE_SCORING,
        SCALE_BEHIND_SCORING,
        STRAIGHT_UP,
        FEEDER
    };

enum class WantedScaleScoreHeight {
    HIGH_SCALE,
    MID_SCALE
};

class SuperStructure : public CORETask {
public:
    SystemState m_actualSystemState;
    SuperStructure();
    void robotInitTask() override;
    void teleopInitTask() override;
    void postLoopTask() override;

    void setWantedState(WantedState wantedState);
    void setWantedScaleScoreHeight(WantedScaleScoreHeight wantedHeight);
    WantedState getWantedState();
    SystemState getSystemState();

private:

    enum class GrabCubeState {
        WAITING_FOR_CUBE,
        MOVING_DOWN_TO_CUBE,
        MOVING_UP_TO_CUBE_CLEARANCE,
        CUBE_CLEARANCE_HEIGHT
    };

    SystemState handleTransit();
    SystemState handleGrabbingCube();
    SystemState handleSwitchScoring();
    SystemState handleScaleScoring();
    SystemState handleBehindScaleScoring();
    SystemState handleFeeder();
    SystemState handleStraightUp();

    WantedState m_wantedState;
    SystemState m_systemState;
    GrabCubeState m_grabCubeState;
    WantedScaleScoreHeight m_wantedScaleScoreHeight;

    LiftSubsystem * m_liftSubsystem;
    ScorerSubsystem * m_scorerSubsystem;
    ChainBarSubsystem * m_chainBarSubsystem;

    COREConstant<double> m_transitTransitionTimeout, m_grabCubeTimeout;

    CORETimer m_timeoutTimer;
    CORETimer m_cubeTimer;
    bool m_cubeTimerStarted;
};
