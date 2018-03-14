
#pragma once

#include "COREFramework/CORETask.h"
#include <WPILib.h>

using namespace CORE;
enum side {
	LEFT,
	RIGHT
};
class GameDataParser : public CORETask {

	void autonInitTask() override;
	side getSwitchSide();
	side getScaleSide();
	side switchSide;
	side scaleSide;

private:


};
