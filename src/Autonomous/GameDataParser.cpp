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

side GameDataParser::getGameOrientation() {
	return m_parsedGameOrientation;
}

void GameDataParser::robotInitTask() {
	m_cubePlacementChooser = new SendableChooser<cubePlacement>();
	m_cubePlacementChooser->AddDefault("1 Switch", SWITCH1);
	m_cubePlacementChooser->AddObject("1 Scale", SCALE1);
	m_cubePlacementChooser->AddObject("1 Switch, 1 Scale", SWITCH1SCALE1);
	m_cubePlacementChooser->AddObject("1 Switch, 2 Scale", SWITCH1SCALE2);
	SmartDashboard::PutData(m_cubePlacementChooser);

	m_startingPositonChooser = new SendableChooser<startingPosition>();
	m_startingPositonChooser->AddDefault("Right Side", RIGHT_SIDE);
	m_startingPositonChooser->AddObject("Center", CENTER);
	m_startingPositonChooser->AddObject("Left Side", LEFT_SIDE);
	SmartDashboard::PutData(m_startingPositonChooser);
}

startingPosition GameDataParser::getStartingPosition() {
	return m_startingPositonChooser->GetSelected();
}

cubePlacement GameDataParser::getCubePlacement() {
	return m_cubePlacementChooser->GetSelected();
}

Path GameDataParser::loadPath(sidePath pathName, bool flip) {
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
	}
	return PathLoader::loadPath(fileName, flip, false);
}

Path GameDataParser::loadPath(centerPath pathName, bool flip) {
	string fileName;
	switch(pathName) {
		case centerPath::DRIVE_FORWARD:
			fileName = "centerDriveForward.json";
			break;
		case centerPath::WALL_TO_SWITCH:
			fileName = "centerWallToSwitch.json";
			break;

	}
}

Path GameDataParser::getWallToSwitchPath() {
	Path path;
	if(getStartingPosition() == RIGHT_SIDE) {
		if(getGameOrientation() == RR || getGameOrientation() == RL) {
			path = loadPath(sidePath::WALL_TO_SWITCH, false);
		} else {
			path = loadPath(sidePath::WALL_TO_OPPOSITE_SWITCH, false);
		}
	} else if(getStartingPosition() == LEFT_SIDE) {
		if(getGameOrientation() == LL || getGameOrientation() == LR) {
			path = loadPath(sidePath::WALL_TO_SWITCH, true);
		} else {
			path = loadPath(sidePath::WALL_TO_OPPOSITE_SWITCH, true);
		}
	} else {
		path = loadPath(centerPath::WALL_TO_SWITCH, !(getGameOrientation() == RR || getGameOrientation() == RL));
	}
	return path;
}
Path GameDataParser::getWallToScalePath() {
    Path path;
    if(getStartingPosition() == RIGHT_SIDE) {
        if(getGameOrientation() == RR || getGameOrientation() == RL) {
            path = loadPath(sidePath::WALL_TO_SCALE, false);
        } else {
            path = loadPath(sidePath::WALL_TO_OPPOSITE_SCALE, false);
        }
    } else if(getStartingPosition() == LEFT_SIDE) {
        if(getGameOrientation() == LL || getGameOrientation() == LR) {
            path = loadPath(sidePath::WALL_TO_SCALE, true);
        } else {
            path = loadPath(sidePath::WALL_TO_OPPOSITE_SCALE, true);
        }
    } else {
        //path = loadPath(centerPath::WALL_TO_SWITCH, !(getGameOrientation() == RR || getGameOrientation() == RL));
    }
    return path;
}


