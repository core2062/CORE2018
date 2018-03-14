#include "GameDataParser.h"
#include <WPILib.h>
#include "CORELogging/CORELog.h"


void GameDataParser::autonInitTask() {
	std::string gameOrientation = DriverStation::GetInstance().GetGameSpecificMessage();

	if (gameOrientation[0] == 'L') {
		switchSide = LEFT;
	} else {
		switchSide = RIGHT;
	}
	if (gameOrientation[1] == 'L') {
		scaleSide = LEFT;
	} else {
		scaleSide = RIGHT;
	}
	CORELog::logInfo("Game Orientation: " + gameOrientation);
	}
side GameDataParser::getScaleSide() {
	return scaleSide;
}
side GameDataParser::getSwitchSide() {
	return switchSide;
}

