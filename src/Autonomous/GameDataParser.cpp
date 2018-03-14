#include "GameDataParser.h"
#include <WPILib.h>
#include "CORELogging/CORELog.h"


void GameDataParser::autonInitTask() {
	std::string gameOrientation = DriverStation::GetInstance().GetGameSpecificMessage();

	if (gameOrientation[0] == 'L' && gameOrientation[1] == 'L') {
		parsedGameOrientation = LL;
	} else if (gameOrientation[0] == 'L' && gameOrientation[1] == 'R'){
		parsedGameOrientation = LR;
	} else if (gameOrientation[0] == 'R' && gameOrientation[1] == 'L') {
		 parsedGameOrientation= RL;
	} else if (gameOrientation[0] == 'R' && gameOrientation[1] == 'R'){
		parsedGameOrientation = RR;
	}
	CORELog::logInfo("Game Orientation: " + gameOrientation);
}
side GameDataParser::getGameOrientation() {
	return parsedGameOrientation;
}


