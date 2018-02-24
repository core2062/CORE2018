#include <Autonomous/Action/LiftUpToSwitch.h>

LiftUpToSwitch::LiftUpToSwitch() {
}
void LiftUpToSwitch::actionInit(){
}
COREAutonAction::actionStatus LiftUpToSwitch::action(){
	liftSubsystem.setLift(0.2);
	liftSubsystem.setLift(0);
	return COREAutonAction::actionStatus::END;
}
void LiftUpToSwitch::actionEnd(){

}

