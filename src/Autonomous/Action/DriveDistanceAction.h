#pragma once

#include <CORERobotLib.h>

class DriveDistanceAction : public COREAutonAction {
public:
	DriveDistanceAction();
	void actionInit() override;
	actionStatus action() override;
	void actionEnd() override;
};