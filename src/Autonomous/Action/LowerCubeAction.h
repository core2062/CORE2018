#pragma once

#include <CORERobotlib.h>

class LowerCubeAction: public COREAutonAction {
public:
	LowerCubeAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
};

