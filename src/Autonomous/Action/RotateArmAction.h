#pragma once

#include <CORERobotLib.h>
#include <ScorerSubsystem.h>
#include "COREUtilities/COREConstant.h"

enum rotateArmAction{
	UP,
	MIDDLE,
	DOWN
};

class RotateArmAction : public COREAutonAction {
public:
	RotateArmAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	ScorerSubsystem scorerSubsystem;

private:
	COREConstant <double> m_upChainBarAngle, m_downChainBarAngle, m_middleChainBarAngle;
	rotateArmAction m_requestedArmAction;
};
