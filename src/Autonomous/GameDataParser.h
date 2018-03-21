#pragma once

#include "CORERobotLib.h"
#include <WPILib.h>

using namespace CORE;

enum side {
	LL,
	LR,
	RL,
	RR
};

enum cubePlacement {
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
    WALL_TO_SWITCH
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
	side getGameOrientation();
	Path loadPath(sidePath pathName, bool flip);
    Path loadPath(centerPath pathName, bool flip);
    startingPosition getStartingPosition();
    cubePlacement getCubePlacement();

    Path getWallToSwitchPath();
    Path getWallToScalePath();

private:
	side m_parsedGameOrientation;
    SendableChooser<cubePlacement> *m_cubePlacementChooser;
    SendableChooser<startingPosition> *m_startingPositonChooser;
};
