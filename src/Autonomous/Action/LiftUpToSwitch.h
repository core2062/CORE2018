#pragma once

#include <LiftSubsystem.h>
#include <CORERobotlib.h>


class LiftUpToSwitch : public COREAutonAction {
public:
	LiftUpToSwitch();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	LiftSubsystem liftSubsystem;
};
