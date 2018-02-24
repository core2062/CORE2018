#include <Autonomous/Action/LiftUpToScale.h>

LiftUpToScale::LiftUpToScale() {
}
void LiftUpToScale::actionInit(){

}
COREAutonAction::actionStatus LiftUpToScale::action(){
	liftSubsystem.setLift(0.2);
	liftSubsystem.setLift(0);
	return COREAutonAction::actionStatus::END;
}
void LiftUpToScale::actionEnd(){

}
