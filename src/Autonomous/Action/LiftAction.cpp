#include <Autonomous/Action/LiftAction.h>
#include "Robot.h"

LiftAction::LiftAction(liftAction action) {

	m_requestedLiftAction = action;

}

LiftAction::LiftAction(int newPosition) {

}

void LiftAction::actionInit(){

}

COREAutonAction::actionStatus LiftAction::action(){
	//TODO add top, bottom, scale, and switch functions to Lift Subsystem
	switch(m_requestedLiftAction) {

	case TOP:
		CORE2018::GetInstance()->liftSubsystem.SetRequestedPosition(200000);
		break;
	case BOTTOM:
		CORE2018::GetInstance()->liftSubsystem.SetRequestedPosition(1000);
		break;
	case SCALE:
		CORE2018::GetInstance()->liftSubsystem.SetRequestedPosition(200000);
		break;
	case SWITCH:
		CORE2018::GetInstance()->liftSubsystem.SetRequestedPosition(200000);
		break;
	default:
		break;

	}
	return COREAutonAction::actionStatus::END;
}
void LiftAction::actionEnd(){

}
