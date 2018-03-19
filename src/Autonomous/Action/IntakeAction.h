#pragma once

#include <CORERobotLib.h>
#include <IntakeSubsystem.h>
#include <ScorerSubsystem.h>
#include "COREUtilities/COREConstant.h"

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
	COREConstant<double> m_outtakeSpeed, m_intakeSpeed;
	intake m_intakeRequestedAction;
};
