#pragma once

#include <CORERobotlib.h>
#include <IntakeSubsystem.h>
#include <ScorerSubsystem.h>

class IntakeAction : public COREAutonAction {
public:
	IntakeAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	bool cubeInScorer();
	IntakeSubsystem intakeSubsystem;
	ScorerSubsystem scorerSubsystem;
};