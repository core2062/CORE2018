#pragma once

#include <CORERobotLib.h>
#include "LiftSubsystem.h"
#include "ScorerSubsystem.h"
#include "ChainBarSubsystem.h"
#include "COREUtilities/COREConstant.h"
#include "COREFramework/COREScheduler.h"

using namespace CORE;

class SuperStructure : public CORESubsystem, public CORETask {
public:
    SuperStructure();
    void robotInit() override;
    void postLoopTask() override;

    enum class WantedState {
        WANT_TO_PICKUP_CUBE, //We want to pickup a cube
        WANT_TO_SCORE_ON_SCALE, //We want to score on the scale
        WANT_TO_SCORE_ON_SCALE_BEHIND, //We want to score on the scale, but behind us
        WANT_TO_SCORE_ON_SWITCH //We want to score on the switch
    };

    void setWantedState(WantedState wantedState);


private:
    enum class SystemState {
        TRANSIT_BELOW_CHANGE_POINT,
        TRANSIT_ABOVE_CHANGE_POINT,
        GRABBING_CUBE,
        SWITCH_SCORING,
        SCALE_SCORING,
        SCALE_BEHIND_SCORING,
        STRAIGHT_UP
    };

    enum class GrabCubeState {
        WAITING_FOR_CUBE,
        MOVING_DOWN_TO_CUBE,
        MOVING_UP_TO_SAFE,
        CUBE_SAFE_HEIGHT
    };

    enum class ScaleScoreState {
        HIGH_SCALE,
        MID_SCALE,
        LOW_SCALE
    };

    WantedState m_wantedState;
    SystemState m_systemState;
    GrabCubeState m_grabCubeState;
    ScaleScoreState m_scaleScoreState;
    SystemState handleGrabbingCube();
    SystemState switchScoring();
    SystemState scaleScoring();
    SystemState behindScaleScoring();

    LiftSubsystem * m_liftSubsystem;
    ScorerSubsystem * m_scorerSubsystem;
    ChainBarSubsystem * m_chainBarSubsystem;

    COREConstant<double> m_scaleHighHeight, m_scaleMediumHeight, m_scaleLowHeight,
		m_switchHeight, m_cubeClearanceHeight, m_cubeSafeHeight, m_forwardRotationScoringAngle,
		m_backwardsRotationScoringAngle;
};