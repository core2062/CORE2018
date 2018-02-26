#pragma once

#include <CORERobotlib.h>
#include <IntakeSubsystem.h>
#include <ScorerSubsystem.h>

class IntakeCubeAction : public COREAutonAction {
public:
	IntakeCubeAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	IntakeSubsystem intakeSubsystem;
	ScorerSubsystem scorerSubsystem;
};