#include "GameDataParser.h"
#include <WPILib.h>
#include "CORELogging/CORELog.h"

void GameDataParser::autonInitTask() {
	std::string gameOrientation = driverStation.GetGameSpecificMessage();

	if (gameOrientation[0] == 'L' && gameOrientation[1] == 'L') {

	} else if (gameOrientation[0] == 'L' && gameOrientation[1] == 'R') {

	} else if (gameOrientation[0] == 'R' && gameOrientation[1] == 'L') {

	} else if (gameOrientation[0] == 'R' && gameOrientation[1] == 'R') {

	} else {
		CORELog::logInfo("Game Orientation is not valid!");
	}
}

