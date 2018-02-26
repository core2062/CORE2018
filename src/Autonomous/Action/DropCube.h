#pragma once

#include <CORERobotLib.h>
#include <ScorerSubsystem.h>


class DropCube : public COREAutonAction{
public:
	DropCube();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	ScorerSubsystem scorerSubsystem;
};
