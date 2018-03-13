#include <Autonomous/Action/LiftAction.h>
#include "Robot.h"

LiftAction::LiftAction(liftAction action) {

	m_requestedLiftAction = action;

}

LiftAction::LiftAction(int newPosition) {

}

void LiftAction::actionInit(){
	//TODO add top, bottom, scale, and switch functions to Lift Subsystem
	switch(m_requestedLiftAction) {

	case TOP:


		break;
	case BOTTOM:

		break;
	case SCALE:
		break;
	case SWITCH:

		break;
	default:
		break;


	}
}

COREAutonAction::actionStatus LiftAction::action(){



	//TODO: Write this code
	return COREAutonAction::actionStatus::END;
}
void LiftAction::actionEnd(){

}
