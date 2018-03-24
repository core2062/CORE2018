#include <Autonomous/Action/LiftAction.h>
#include "Robot.h"
#include "COREUtilities/COREConstant.h"

LiftAction::LiftAction(liftAction action) :
	m_bottomHeight("Lift Bottom Height Value"),
	m_topHeight("Lift Top Height Value"),
	m_switchHeight("Switch Height Value"),
	m_scaleHeight("Scale Height Value") {

	m_requestedLiftAction = action;

}

void LiftAction::actionInit(){

}

COREAutonAction::actionStatus LiftAction::action(){
	//TODO add top, bottom, scale, and switch functions to Lift Subsystem
	switch(m_requestedLiftAction) {

	case TOP:
		CORE2018::GetInstance()->liftSubsystem.SetRequestedPosition(m_topHeight.Get());
		break;
	case BOTTOM:
		CORE2018::GetInstance()->liftSubsystem.SetRequestedPosition(m_bottomHeight.Get());
		break;
	case SCALE:
		CORE2018::GetInstance()->chainBarSubsystem.SetChainBarRequestedAngle(-90);
		CORE2018::GetInstance()->chainBarSubsystem.SetRotationRequestedAngle(-90);
		CORE2018::GetInstance()->liftSubsystem.SetRequestedPosition(m_scaleHeight.Get());
		break;
	case SWITCH:
//		CORE2018::GetInstance()->liftSubsystem.SetRequestedPosition(15);
		CORE2018::GetInstance()->chainBarSubsystem.SetChainBarRequestedAngle(-90);
		CORE2018::GetInstance()->chainBarSubsystem.SetRotationRequestedAngle(-90);
		break;
	default:
		break;

	}
	return COREAutonAction::actionStatus::END;
}
void LiftAction::actionEnd(){

}
