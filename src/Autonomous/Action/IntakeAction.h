#pragma once

#include <CORERobotLib.h>
#include <IntakeSubsystem.h>
#include <ScorerSubsystem.h>
#include "COREUtilities/COREConstant.h"

enum intakeAction {
	WIDE_RANGE_INTAKE,
	SMALL_RANGE_INTAKE,
	OUTTAKE_CUBE,
	STOP
};
class IntakeAction : public COREAutonAction {
public:
	IntakeAction(intakeAction intakeRequestedAction);
	void actionInit();
	actionStatus action() override;
	void actionEnd();

private:
	intakeAction m_intakeRequestedAction;
};
