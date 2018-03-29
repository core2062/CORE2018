#pragma once

#include <CORERobotLib.h>
#include "LiftSubsystem.h"
#include "ScorerSubsystem.h"
#include "ChainBarSubsystem.h"

using namespace CORE;

enum class WantedState {
    WANT_TO_PICKUP_CUBE, //We want to pickup a cube
    WANT_TO_SCORE_ON_SCALE, //We want to score on the scale
    WANT_TO_SCORE_ON_SCALE_BEHIND, //We want to score on the scale, but behind us
    WANT_TO_SCORE_ON_SWITCH, //We want to score on the switch
    TRANSIT
};

class SuperStructure : public CORETask {
public:
    SuperStructure();
    void robotInitTask() override;
    void teleopInitTask() override;
    void postLoopTask() override;

    void setWantedState(WantedState wantedState);

private:

    enum class SystemState {
        TRANSIT,
        GRABBING_CUBE,
        SWITCH_SCORING,
        SCALE_SCORING,
        SCALE_BEHIND_SCORING,
        STRAIGHT_UP
    };

    enum class GrabCubeState {
        WAITING_FOR_CUBE,
        MOVING_DOWN_TO_CUBE,
        MOVING_UP_TO_CUBE_CLEARANCE,
        CUBE_CLEARANCE_HIEGHT
    };

    enum class ScaleScoreState {
        HIGH_SCALE,
        MID_SCALE,
        LOW_SCALE
    };

    SystemState handleGrabbingCube();


    WantedState m_wantedState;
    SystemState m_systemState;
    GrabCubeState m_grabCubeState;
    ScaleScoreState m_scaleScoreState;

    LiftSubsystem * m_liftSubsystem;
    ScorerSubsystem * m_scorerSubsystem;
    ChainBarSubsystem * m_chainBarSubsytem;

    COREConstant<double> m_liftCubeClearanceHeight;
};