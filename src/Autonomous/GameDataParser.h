#pragma once

#include "CORERobotLib.h"
#include <WPILib.h>

using namespace CORE;

enum orientation {
	LL,
	LR,
	RL,
	RR
};

enum side {
    LEFT,
    RIGHT
};

enum cubePlacement {
    DRIVE_FORWARD,
    SWITCH1,
    SCALE1,
    SWITCH1SCALE1,
    SWITCH1SCALE2
};

enum class sidePath {
    DRIVE_FORWARD,
    WALL_TO_SWITCH,
    WALL_TO_OPPOSITE_SWITCH,
    WALL_TO_SCALE,
    WALL_TO_OPPOSITE_SCALE,
    SWITCH_TO_SCALE,
    SWITCH_TO_OPPOSITE_SCALE,
};

enum class centerPath {
    DRIVE_FORWARD,
    WALL_TO_LEFT_SWITCH,
	WALL_TO_RIGHT_SWITCH
};

enum startingPosition {
    LEFT_SIDE,
    CENTER,
    RIGHT_SIDE,
};

class GameDataParser : public CORETask {
public:
    void robotInitTask() override;
    void autonInitTask() override;
	orientation getGameOrientation();
    bool IsSwitchRight();
    bool IsSwitchLeft();
    bool IsScaleRight();
    bool IsScaleLeft();
	Path LoadPath(sidePath pathName, bool flip);
    Path LoadPath(centerPath pathName, bool flip);
    startingPosition GetStartingPosition();
    cubePlacement GetCubePlacement();
    Path GetWallToSwitchPath();
    Path GetWallToScalePath();

private:
	orientation m_parsedGameOrientation;
    SendableChooser<cubePlacement> *m_cubePlacementChooser;
    SendableChooser<startingPosition> *m_startingPositonChooser;
};
