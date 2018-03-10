#pragma once

#include <CORERobotlib.h>
#include <IntakeSubsystem.h>
#include <ScorerSubsystem.h>
enum intake {
	INTAKE,
	OUTTAKE,
	CLOSE,
	OPENINTAKE,
	STOP
};
class IntakeAction : public COREAutonAction {
public:
	IntakeAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	bool cubeInScorer();
	IntakeSubsystem intakeSubsystem;
	ScorerSubsystem scorerSubsystem;
private:
	intake m_intakeRequestedAction;
};
