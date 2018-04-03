#include "GameDataParser.h"

void GameDataParser::autonInitTask() {
	std::string gameOrientation = DriverStation::GetInstance().GetGameSpecificMessage();

	if (gameOrientation[0] == 'L' && gameOrientation[1] == 'L') {
		m_parsedGameOrientation = LL;
	} else if (gameOrientation[0] == 'L' && gameOrientation[1] == 'R'){
		m_parsedGameOrientation = LR;
	} else if (gameOrientation[0] == 'R' && gameOrientation[1] == 'L') {
		 m_parsedGameOrientation= RL;
	} else if (gameOrientation[0] == 'R' && gameOrientation[1] == 'R'){
		m_parsedGameOrientation = RR;
	}
	CORELog::logInfo("Game Orientation: " + gameOrientation);
}

orientation GameDataParser::getGameOrientation() {
	return m_parsedGameOrientation;
}

void GameDataParser::robotInitTask() {
	m_cubePlacementChooser = new SendableChooser<cubePlacement>();
	m_cubePlacementChooser->AddDefault("1 Switch", SWITCH1);
	m_cubePlacementChooser->AddObject("1 Scale", SCALE1);
	m_cubePlacementChooser->AddObject("1 Switch, 1 Scale", SWITCH1SCALE1);
	m_cubePlacementChooser->AddObject("1 Switch, 2 Scale", SWITCH1SCALE2);
	SmartDashboard::PutData("Cube Placement", m_cubePlacementChooser);

	m_startingPositonChooser = new SendableChooser<startingPosition>();
	m_startingPositonChooser->AddDefault("Right Side", RIGHT_SIDE);
	m_startingPositonChooser->AddObject("Center", CENTER);
	m_startingPositonChooser->AddObject("Left Side", LEFT_SIDE);
	SmartDashboard::PutData("Starting Position", m_startingPositonChooser);
}

startingPosition GameDataParser::GetStartingPosition() {
	return m_startingPositonChooser->GetSelected();
}

cubePlacement GameDataParser::GetCubePlacement() {
	return m_cubePlacementChooser->GetSelected();
}

Path GameDataParser::LoadPath(sidePath pathName, bool flip) {
	string fileName;
	switch(pathName) {
		case sidePath::DRIVE_FORWARD:
			fileName = "sideDriveForward.json";
			break;
		case sidePath::WALL_TO_SWITCH:
			fileName = "sideWallToSwitch.json";
			break;
		case sidePath::WALL_TO_OPPOSITE_SWITCH:
			fileName = "sideWallToOppositeSwitch.json";
			break;
		case sidePath::WALL_TO_SCALE:
			fileName = "sideWallToScale.json";
			break;
		case sidePath::WALL_TO_OPPOSITE_SCALE:
			fileName = "sideWallToOppositeScale.json";
			break;
		case sidePath::SWITCH_TO_SCALE:
			fileName = "sideSwitchToScale.json";
			break;
		case sidePath::SWITCH_TO_OPPOSITE_SCALE:
			fileName = "sideSwitchToOppositeScale.json";
			break;
		case sidePath::SCALE_TO_CUBE:
			fileName = "sideScaleToCube.json";
			break;
		case sidePath::SCALE_TO_OPPOSITE_CUBE:
			fileName = "sideScaleToOppositeCube.json";
			break;
	}
	return Path::fromFile(fileName, flip);
}

Path GameDataParser::LoadPath(centerPath pathName, bool flip) {
	string fileName;
	switch(pathName) {
		case centerPath::DRIVE_FORWARD:
			fileName = "centerDriveForward.json";
			break;
		case centerPath::WALL_TO_LEFT_SWITCH:
			fileName = "centerWallToLeftSwitch.json";
			break;
        case centerPath::WALL_TO_RIGHT_SWITCH:
            fileName = "centerWallToRightSwitch.json";
            break;
    }
	return Path::fromFile(fileName, flip);
}

Path GameDataParser::GetWallToSwitchPath() {
	Path path;
    switch (GetStartingPosition()) {
        case RIGHT_SIDE:
            if(IsSwitchRight()) {
                path = LoadPath(sidePath::WALL_TO_SWITCH, false);
            } else {
                path = LoadPath(sidePath::WALL_TO_OPPOSITE_SWITCH, false);
            }
            break;
        case LEFT_SIDE:
            if(IsSwitchLeft()) {
                path = LoadPath(sidePath::WALL_TO_SWITCH, true);
            } else {
                path = LoadPath(sidePath::WALL_TO_OPPOSITE_SWITCH, true);
            }
            break;
        case CENTER:
            if(IsSwitchRight()) {
                path = LoadPath(centerPath::WALL_TO_RIGHT_SWITCH, false);
            } else {
                path = LoadPath(centerPath::WALL_TO_LEFT_SWITCH, false);
            }

            break;
    }
	return path;
}

Path GameDataParser::GetWallToScalePath() {
    Path path;
    if(GetStartingPosition() == RIGHT_SIDE) {
        if(IsScaleRight()) {
            path = LoadPath(sidePath::WALL_TO_SCALE, false);
        } else {
            path = LoadPath(sidePath::WALL_TO_OPPOSITE_SCALE, false);
        }
    } else if(GetStartingPosition() == LEFT_SIDE) {
        if(IsScaleLeft()) {
            path = LoadPath(sidePath::WALL_TO_SCALE, true);
        } else {
            path = LoadPath(sidePath::WALL_TO_OPPOSITE_SCALE, true);
        }
    } else {
        //path = loadPath(centerPath::WALL_TO_SWITCH, !(getGameOrientation() == RR || getGameOrientation() == RL));
    }
    return path;
}

Path GameDataParser::GetScaleToCubePath() {
	Path path;
		if(IsScaleRight()) {
			if(IsSwitchRight()) {
				path = LoadPath(sidePath::SCALE_TO_CUBE, false);
			} else {
				path = LoadPath(sidePath::SCALE_TO_OPPOSITE_CUBE, false);
			}
		} else {
			if(IsSwitchRight()) {
				path = LoadPath(sidePath::SCALE_TO_OPPOSITE_CUBE, true);
			} else {
				path = LoadPath(sidePath::SCALE_TO_CUBE, true);
			}
		}
	return path;
}

bool GameDataParser::IsSwitchRight() {
    return (getGameOrientation() == RR || getGameOrientation() == RL);
}

bool GameDataParser::IsScaleRight() {
    return (getGameOrientation() == RR || getGameOrientation() == LR);
}

bool GameDataParser::IsSwitchLeft() {
    return !IsSwitchRight();
}

bool GameDataParser::IsScaleLeft() {
    return !IsScaleRight();
}


