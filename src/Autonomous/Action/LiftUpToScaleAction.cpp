#include <Autonomous/Action/LiftUpToScaleAction.h>
#include "Robot.h"

LiftUpToScaleAction::LiftUpToScaleAction() {
 m_scaleHeight = 7.0;
}
void LiftUpToScaleAction::actionInit(){

}
COREAutonAction::actionStatus LiftUpToScaleAction::action(){
	if (Robot.liftSubsystem.m_liftPosition <= m_scaleHeight) {
		Robot.liftSubsystem.setLift(0.2);
		return COREAutonAction::actionStatus::CONTINUE;
	} else {
		Robot.liftSubsystem.setLift(0);
		return COREAutonAction::actionStatus::END;
	}
}
void LiftUpToScaleAction::actionEnd(){

}
