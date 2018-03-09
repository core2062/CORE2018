#pragma once

#include <CORERobotLib.h>
#include <ScorerSubsystem.h>
#include <Robot.h>


class DropCubeAction : public COREAutonAction{
public:
	DropCubeAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	CORE2018 Robot;
};
