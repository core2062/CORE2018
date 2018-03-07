
#pragma once

#include "COREFramework/CORETask.h"
#include <WPILib.h>

using namespace CORE;

class GameDataParser : public CORETask {

	void autonInitTask() override;
	DriverStation driverStation;

private:

};
