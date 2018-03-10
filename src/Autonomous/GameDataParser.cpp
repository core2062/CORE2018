#include "GameDataParser.h"
#include <WPILib.h>
#include "CORELogging/CORELog.h"

void GameDataParser::autonInitTask() {
	std::string gameOrientation = DriverStation::GetInstance().GetGameSpecificMessage();

	if (gameOrientation[0] == 'L') {
		m_switchSide = LEFT;
	} else {
		m_switchSide = RIGHT;
	}
	if (gameOrientation[1] == 'L') {
		m_scaleSide = LEFT;
	} else {
		m_scaleSide = RIGHT;
	}
	CORELog::logInfo("Game Orientation: " + gameOrientation);
	}
side GameDataParser::getScaleSide() {
	return m_scaleSide;
}
side GameDataParser::getSwitchSide() {
	return m_switchSide;
}

