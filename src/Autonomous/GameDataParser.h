
#pragma once

#include "COREFramework/CORETask.h"
#include <WPILib.h>

using namespace CORE;
enum side {
	LL,
	LR,
	RL,
	RR
};
class GameDataParser : public CORETask {
public:
	void autonInitTask() override;
	side getGameOrientation();
	side parsedGameOrientation;


private:


};
