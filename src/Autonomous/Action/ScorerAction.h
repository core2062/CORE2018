#pragma once

#include "CORERobotLib.h"

enum scorerAction {
	CLOSED,
	OPEN,
	WAIT_FOR_CUBE
};

class ScorerAction : public COREAutonAction {
public:
	ScorerAction(scorerAction action);
	void actionInit() override;
	actionStatus action() override;
	void actionEnd() override;

private:
	scorerAction m_requestedAction;
};
