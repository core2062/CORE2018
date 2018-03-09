#include <Autonomous/Action/LiftAction.h>
#include "Robot.h"

LiftAction::LiftAction(liftAction action) {

}

LiftAction::LiftAction(int newPosition) {

}

void LiftAction::actionInit(){

}

COREAutonAction::actionStatus LiftAction::action(){
/*	if (Robot.liftSubsystem.m_liftPosition <= m_scaleHeight) {
		Robot.liftSubsystem.setLift(0.2);
		return COREAutonAction::actionStatus::CONTINUE;
	} else {
		Robot.liftSubsystem.setLift(0);
		return COREAutonAction::actionStatus::END;
	}*/
	//TODO: Write this code
	return COREAutonAction::actionStatus::END;
}
void LiftAction::actionEnd(){

}
