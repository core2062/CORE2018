#pragma once

#include <LiftSubsystem.h>
#include <CORERobotlib.h>


class LiftUpToScale: public COREAutonAction{
public:
	LiftUpToScale();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	LiftSubsystem liftSubsystem;
};
