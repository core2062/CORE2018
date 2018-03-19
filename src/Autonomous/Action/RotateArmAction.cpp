#include <Autonomous/Action/RotateArmAction.h>
#include <CORERobotLib.h>
#include <Robot.h>
#include "COREUtilities/COREConstant.h"

RotateArmAction::RotateArmAction():
	m_upChainBarAngle("Up Chain Bar Angle"),
	m_downChainBarAngle("Down Chain Bar Angle"),
	m_middleChainBarAngle("Middle Chain Bar Angle") {

}
void RotateArmAction::actionInit() {

}
COREAutonAction::actionStatus RotateArmAction::action() {
	switch(m_requestedArmAction) {
	case UP:
		CORE2018::GetInstance()->chainBarSubsystem.SetRotationRequestedAngle(m_upChainBarAngle.Get());
		break;
	case MIDDLE:
		CORE2018::GetInstance()->chainBarSubsystem.SetRotationRequestedAngle(m_middleChainBarAngle.Get());
		break;
	case DOWN:
		CORE2018::GetInstance()->chainBarSubsystem.SetRotationRequestedAngle(m_downChainBarAngle.Get());
		break;
	}
	return COREAutonAction::actionStatus::END;
}
void RotateArmAction::actionEnd() {

}
